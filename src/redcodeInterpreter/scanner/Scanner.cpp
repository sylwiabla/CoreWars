//
// Created by Sylwia Blach on 4/19/17.
//

#include "Scanner.hpp"

Scanner::Keywords Scanner::keywords_ = {{"#", Token::Type (Token::immediateMode, "immediate addressing mode")},
                                        {"$", Token::Type(Token::directMode, "direct addressing mode")},
                                        {"@", Token::Type(Token::indirectMode, "indirect addressing mode")},
                                        {"A", Token::Type (Token::AModifier, "a modifier")},
                                        {"B", Token::Type(Token::BModifier, "b modifier")},
                                        {"AB", Token::Type(Token::ABModifier, "a - b modifier")},
                                        {"BA", Token::Type(Token::BAModifier, "b - a modifier")},
                                        {"F", Token::Type(Token::FModifier, "f modifier")},
                                        {"X", Token::Type(Token::XModifier, "x modifier")},
                                        {"I", Token::Type(Token::IModifier, "i modifier")},
                                        {"equ", Token::Type(Token::equ, "equ")},
                                        {"end", Token::Type(Token::end, "end")},
                                        {"for", Token::Type(Token::forType, "for loop")},
                                        {"rof", Token::Type(Token::rof, "rof")},
                                        {"uqe", Token::Type(Token::uqe, "uqe")},
                                        {"dat", Token::Type(Token::dat, "dat")},
                                        {"mov", Token::Type(Token::mov, "mov")},
                                        {"add", Token::Type(Token::add, "add")},
                                        {"sub", Token::Type(Token::sub, "sub")},
                                        {"mul", Token::Type(Token::mul, "mul")},
                                        {"div", Token::Type(Token::div, "div")},
                                        {"mod", Token::Type(Token::mod, "mod")},
                                        {"jmz", Token::Type(Token::jmz, "jmz")},
                                        {"jmn", Token::Type(Token::jmn, "jmn")},
                                        {"djn", Token::Type(Token::djn, "djn")},
                                        {"spl", Token::Type(Token::spl, "spl")},
                                        {"cmp", Token::Type(Token::cmp, "cmp")},
                                        {"seq", Token::Type(Token::seq, "seq")},
                                        {"sne", Token::Type(Token::sne, "sne")},
                                        {"slt", Token::Type(Token::slt, "slt")},
                                        {"jmp", Token::Type(Token::jmp, "jmp")},
                                        {"nop", Token::Type(Token::nop, "nop")},
                                        {",", Token::Type(Token::comma, "comma")},
                                        {".", Token::Type(Token::dot, "dot")}};

TokenPtr Scanner::getToken ()
{
    TokenPtr token;
    do
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
            return std::make_shared<Token> (Token::end, "eot");
        token = createToken(c);
    } while (!token);

    return token;
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
        return std::make_shared<Token> (Token::numeric, "numeric", token);

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
    KeywordIter tokenIter = keywords_.find(token);
    if (tokenIter == keywords_.end())
        return std::make_shared<Token> (*(new Token(Token::alpha, "alphanumeric", token)));
    return std::make_shared<Token> (*(new Token(tokenIter->second)));
}

TokenPtr Scanner::createOther(char first)
{
    std::string token = "";
    token += first;
    KeywordIter tokenIter = keywords_.find(token);
    if (tokenIter != keywords_.end())
    {
        Token::Type type = tokenIter->second;
        if ((type == Token::comma) || (type == Token::dot))
            return std::make_shared<Token> (*(new Token(tokenIter->second)));

        char next = sourceCodeManager_->getNext();
        sourceCodeManager_->unget();
        if (isalpha(next) || isdigit(next))
            return std::make_shared<Token> (*(new Token(tokenIter->second)));
        logger_->logError(std::make_shared<Error> (Error (sourceCodeManager_->getLineNr(), "Cannot resolve token: " + token)));
    }
    else
    {
        if(!sourceCodeManager_->endReached())
            logger_->logError(std::make_shared<Error> (Error (sourceCodeManager_->getLineNr(), "Cannot resolve token: " + token)));
    }
    return nullptr;
}