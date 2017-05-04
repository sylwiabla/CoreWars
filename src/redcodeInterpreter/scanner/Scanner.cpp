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
    if (endReached())
        return nullptr;

    if (isdigit(first))
        return createNumeric(first);

    if (isalpha(first))
        return createAlpha(first);

    return createModifier (first);
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
    if (iswspace(c) || (c == RedcodeInterpreter::COMMENT_START) || (c == ','))
        return std::make_shared<Token> (RedcodeInterpreter::numeric, token);

    logger_->logError(std::make_shared<Error> (std::make_tuple<std::string, unsigned int, const std::string> (sourceCodeManager_->getFilename(),
                                                                                                              sourceCodeManager_->getLineNr(), "Bad numeric identifier")));
    return nullptr;
}

TokenPtr Scanner::createAlpha (char first)
{
    std::string token = "";
    token += first;
    char c = sourceCodeManager_->getNext();
    int wordCounter = 1;
    RedcodeInterpreter::TokenIter tokenIter;

    while (isdigit(c) || isalpha(c) || (c == '_'))
    {
        if (wordCounter > MAX_IDENTIFIER_LENGTH)
            logger_->logError(std::make_shared<Error> (std::make_tuple<std::string, unsigned int, const std::string>
                                                               (sourceCodeManager_->getFilename(), sourceCodeManager_->getLineNr(), "Too long identifier")));

        token += c;
        ++wordCounter;
        c = sourceCodeManager_->getNext();
    }

    if (!iswspace(c) && (c != RedcodeInterpreter::COMMENT_START) && (c == ',') && (c != '.'))
    {
        logger_->logError(std::make_shared<Error> (std::make_tuple<std::string, unsigned int, const std::string> (sourceCodeManager_->getFilename(),
                                                                                                                  sourceCodeManager_->getLineNr(), "Bad alphanumeric identifier")));
        return nullptr;
    }

    sourceCodeManager_->unget();
    tokenIter = RedcodeInterpreter::keywords_.find(token);
    if (tokenIter == RedcodeInterpreter::keywords_.end())
        return std::make_shared<Token> (*(new Token(RedcodeInterpreter::alpha, token)));
    else
        return std::make_shared<Token> (*(new Token(tokenIter->second)));
}

TokenPtr Scanner::createModifier(char first)
{
    std::string token = "";
    token += first;
    RedcodeInterpreter::TokenIter tokenIter = RedcodeInterpreter::keywords_.find(token);
    if (tokenIter != RedcodeInterpreter::keywords_.end())
    {
        if (isalpha(sourceCodeManager_->getNext()))
        {
            sourceCodeManager_->unget();
            return std::make_shared<Token> (*(new Token(tokenIter->second)));
        }
        logger_->logError(std::make_shared<Error> (std::make_tuple<std::string, unsigned int, const std::string> (sourceCodeManager_->getFilename(),
                                                                                                                  sourceCodeManager_->getLineNr(), "Cannot resolve token")));
    }
    else
        logger_->logError(std::make_shared<Error> (std::make_tuple<std::string, unsigned int, const std::string> (sourceCodeManager_->getFilename(),
                                                                                                                  sourceCodeManager_->getLineNr(), "Cannot resolve token")));
}