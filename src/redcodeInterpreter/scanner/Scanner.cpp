//
// Created by Sylwia Blach on 4/19/17.
//

#include "Scanner.hpp"

TokenPtr Scanner::getToken ()
{
    omitWhiteSpace();
    char c = sourceCodeManager_->getNext();
    while (c == RedcodeInterpreter::COMMENT_START)
    {
        omitComment();
        omitWhiteSpace();
        c = sourceCodeManager_->getNext();
    }

    return createToken (c);
}

void Scanner::omitComment()
{
    char c = sourceCodeManager_->getNext();

    while (c != '\n')
    {
        if (endReached())
            return;
        c = sourceCodeManager_->getNext();
    }
}

void Scanner::omitWhiteSpace()
{
    char c = sourceCodeManager_->getNext();
    while (iswspace(c))
        c = sourceCodeManager_->getNext();

    sourceCodeManager_->unget();
}

TokenPtr Scanner::createToken (char first)
{
    if (isdigit(first))
        return createNumeric(first);

    if (isalpha(first))
        return createAlpha(first);

    return createOther (first);
}

TokenPtr Scanner::createNumeric (char first)
{
    std::string token = "";
    token += first;
    char c = sourceCodeManager_->getNext();
    while (isdigit(c))
    {
        token += c;
        c = sourceCodeManager_->getNext();
    }

    sourceCodeManager_->unget();
    if (iswspace(c) || (c == RedcodeInterpreter::COMMENT_START) || (c == ',') || (c == EOF))
        return std::make_shared<Token> (RedcodeInterpreter::numeric, token);

    logger_->logError(std::make_shared<Error> (Error (sourceCodeManager_->getLineNr(), "Bad numeric identifier: " + token)));
    return nullptr;
}

TokenPtr Scanner::createAlpha (char first)
{
    std::string token = "";
    token += first;
    char c = sourceCodeManager_->getNext();
    int wordCounter = 1;

    while (isdigit(c) || isalpha(c) || (c == '_'))
    {
        if (wordCounter > MAX_IDENTIFIER_LENGTH)
        {
            logger_->logError(std::make_shared<Error> (Error (sourceCodeManager_->getLineNr(), "Too long identifier: " + token)));
            return nullptr;
        }

        token += c;
        ++wordCounter;
        c = sourceCodeManager_->getNext();
    }

    if (!iswspace(c) && (c != RedcodeInterpreter::COMMENT_START) && (c == ',') && (c != '.') && (c != EOF))
    {
        logger_->logError(std::make_shared<Error> (Error (sourceCodeManager_->getLineNr(), "Bad alphanumeric identifier: " + token)));
        return nullptr;
    }

    sourceCodeManager_->unget();
    RedcodeInterpreter::TokenIter tokenIter = RedcodeInterpreter::keywords_.find(token);
    if (tokenIter == RedcodeInterpreter::keywords_.end())
        return std::make_shared<Token> (*(new Token(RedcodeInterpreter::alpha, token)));
    return std::make_shared<Token> (*(new Token(tokenIter->second)));
}

TokenPtr Scanner::createOther(char first)
{
    std::string token = "";
    token += first;
    RedcodeInterpreter::TokenIter tokenIter = RedcodeInterpreter::keywords_.find(token);
    if (tokenIter != RedcodeInterpreter::keywords_.end())
    {
        if ((tokenIter->second == RedcodeInterpreter::comma))
            return std::make_shared<Token> (*(new Token(tokenIter->second)));

        if (isalpha(sourceCodeManager_->getNext()))
        {
            sourceCodeManager_->unget();
            return std::make_shared<Token> (*(new Token(tokenIter->second, tokenIter->first)));
        }
        sourceCodeManager_->unget();
        logger_->logError(std::make_shared<Error> (Error (sourceCodeManager_->getLineNr(), "Cannot resolve token: " + token)));
    }
    else
    {
        if(!sourceCodeManager_->endReached())
            logger_->logError(std::make_shared<Error> (Error (sourceCodeManager_->getLineNr(), "Cannot resolve token: " + token)));
    }
    return nullptr;
}