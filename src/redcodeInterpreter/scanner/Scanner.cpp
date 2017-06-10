//
// Created by Sylwia Blach on 4/19/17.
//

#include "Scanner.hpp"

const std::unordered_map<std::string, Token::TokenType> Scanner::keywords_ = {{"#", Token::immidiateMode}, {"$", Token::directMode}, {"@", Token::indirectMode}, {"A", Token::AModifier}, {"B", Token::BModifier},
                                                                              {"AB", Token::ABModifier}, {"BA", Token::BAModifier}, {"F", Token::FModifier}, {"X", Token::XModifier}, {"I", Token::IModifier},
                                                                              {"equ", Token::equ}, {"end", Token::end}, {"for", Token::forType}, {"rof", Token::rof}, {"uqe", Token::uqe},
                                                                              {"dat", Token::dat}, {"mov", Token::mov}, {"add", Token::add}, {"sub", Token::sub}, {"mul", Token::mul}, {"div", Token::div},
                                                                              {"mod", Token::mod}, {"jmz", Token::jmz}, {"jmn", Token::jmn}, {"djn", Token::djn}, {"spl", Token::spl}, {"cmp", Token::cmp},
                                                                              {"seq", Token::seq}, {"sne", Token::sne}, {"slt", Token::slt}, {"ldp", Token::ldp}, {"stp", Token::stp}, {"jmp", Token::jmp},
                                                                              {"nop", Token::nop}, {",", Token::comma}, {".", Token::dot}};

TokenPtr Scanner::getToken ()
{
    omitWhiteSpace();
    char c = sourceCodeManager_->getNext();
    while (c == COMMENT_START)
    {
        omitComment();
        omitWhiteSpace();
        c = sourceCodeManager_->getNext();
    }

    if (endReached())
        return nullptr;
    return createToken (c);
}

void Scanner::omitComment()
{
    char c = sourceCodeManager_->getNext();

    while (c != '\n')
    {
        if (endReached())
        {
            sourceCodeManager_->unget();
            return;
        }
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
    if (isdigit(first) || (first == '-'))
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
    if (iswspace(c) || (c == COMMENT_START) || (c == ',') || endReached() || (c == '.'))
        return std::make_shared<Token> (Token::numeric, token);

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

    if (!endReached() && !iswspace(c) && (c != COMMENT_START) && (c != ',') && (c != '.'))
    {
        logger_->logError(std::make_shared<Error> (Error (sourceCodeManager_->getLineNr(), "Bad alphanumeric identifier: " + token)));
        return nullptr;
    }

    sourceCodeManager_->unget();
    TokenIter tokenIter = keywords_.find(token);
    if (tokenIter == keywords_.end())
        return std::make_shared<Token> (*(new Token(Token::alpha, token)));
    return std::make_shared<Token> (*(new Token(tokenIter->second)));
}

TokenPtr Scanner::createOther(char first)
{
    std::string token = "";
    token += first;
    TokenIter tokenIter = keywords_.find(token);
    if (tokenIter != keywords_.end())
    {
        Token::TokenType type = tokenIter->second;
        if ((type == Token::comma) || (type == Token::dot))
            return std::make_shared<Token> (*(new Token(tokenIter->second)));

        char next = sourceCodeManager_->getNext();
        sourceCodeManager_->unget();
        if (isalpha(next) || isdigit(next))
            return std::make_shared<Token> (*(new Token(tokenIter->second, tokenIter->first)));
        logger_->logError(std::make_shared<Error> (Error (sourceCodeManager_->getLineNr(), "Cannot resolve token: " + token)));
    }
    else
    {
        if(!sourceCodeManager_->endReached())
            logger_->logError(std::make_shared<Error> (Error (sourceCodeManager_->getLineNr(), "Cannot resolve token: " + token)));
    }
    return nullptr;
}