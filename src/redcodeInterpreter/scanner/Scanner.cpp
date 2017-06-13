//
// Created by Sylwia Blach on 4/19/17.
//

#include "Scanner.hpp"

Scanner::Keywords Scanner::keywords_ = {{"#", Token::Type (Token::immediateMode, Token::addMode, "immediate addressing mode")},
                                        {"$", Token::Type(Token::directMode, Token::addMode, "direct addressing mode")},
                                        {"@", Token::Type(Token::indirectMode, Token::addMode, "indirect addressing mode")},
                                        {"A", Token::Type (Token::AModifier, Token::modifier, "a modifier")},
                                        {"B", Token::Type(Token::BModifier, Token::modifier, "b modifier")},
                                        {"AB", Token::Type(Token::ABModifier, Token::modifier, "a - b modifier")},
                                        {"BA", Token::Type(Token::BAModifier, Token::modifier, "b - a modifier")},
                                        {"F", Token::Type(Token::FModifier, Token::modifier, "f modifier")},
                                        {"X", Token::Type(Token::XModifier, Token::modifier, "x modifier")},
                                        {"I", Token::Type(Token::IModifier, Token::modifier, "i modifier")},
                                        {"equ", Token::Type(Token::equ, "equ")},
                                        {"end", Token::Type(Token::end, "end")},
                                        {"for", Token::Type(Token::forType, "for loop")},
                                        {"rof", Token::Type(Token::rof, "rof")},
                                        {"uqe", Token::Type(Token::uqe, "uqe")},
                                        {"dat", Token::Type(Token::dat, Token::inst2, "dat")},
                                        {"mov", Token::Type(Token::mov, Token::inst2, "mov")},
                                        {"add", Token::Type(Token::add, Token::inst2, "add")},
                                        {"sub", Token::Type(Token::sub, Token::inst2, "sub")},
                                        {"mul", Token::Type(Token::mul, Token::inst2, "mul")},
                                        {"div", Token::Type(Token::div, Token::inst2, "div")},
                                        {"mod", Token::Type(Token::mod, Token::inst2, "mod")},
                                        {"jmz", Token::Type(Token::jmz, Token::inst2, "jmz")},
                                        {"jmn", Token::Type(Token::jmn, Token::inst2, "jmn")},
                                        {"djn", Token::Type(Token::djn, Token::inst2, "djn")},
                                        {"spl", Token::Type(Token::spl, Token::inst2, "spl")},
                                        {"cmp", Token::Type(Token::cmp, Token::inst2, "cmp")},
                                        {"seq", Token::Type(Token::seq, Token::inst2, "seq")},
                                        {"sne", Token::Type(Token::sne, Token::inst2, "sne")},
                                        {"slt", Token::Type(Token::slt, Token::inst2, "slt")},
                                        {"jmp", Token::Type(Token::jmp, Token::inst1, "jmp")},
                                        {"nop", Token::Type(Token::nop, Token::inst0, "nop")},
                                        {",", Token::Type(Token::comma, "comma")},
                                        {".", Token::Type(Token::dot, "dot")}};

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