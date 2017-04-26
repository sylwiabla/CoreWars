//
// Created by Sylwia Blach on 4/19/17.
//

#include "Scanner.hpp"

const std::unordered_map<char, bool> Scanner::delimiters_ = {{',', true}, {'.', true}};

TokenPtr Scanner::getToken()
{
    omitWhiteSpace();
    char c = sourceCodeManager_->getNext();
    while (c == COMMENT_START)
    {
        omitComment();
        omitWhiteSpace();
        c = sourceCodeManager_->getNext();
    }
    sourceCodeManager_->unget();
    TokenPtr token = createToken ();
    return token;
}

void Scanner::omitComment()
{
    char c = sourceCodeManager_->getNext();

    while (c != '\n')
        c = sourceCodeManager_->getNext();

    ++lineNr_;
}

void Scanner::omitWhiteSpace()
{
    char c = sourceCodeManager_->getNext();
    while (iswspace(c))
    {
        if (c == '\n')
            ++lineNr_;
        c = sourceCodeManager_->getNext();
    }

    sourceCodeManager_->unget();
}

TokenPtr Scanner::createToken ()
{
    char c = sourceCodeManager_->getNext();
    if (RedcodeInterpreter::getInstance().isAddrMode(c))
        return std::make_shared<Token> (new AddressingMode(c));

    TokenPtr token = nullptr;
    if (isdigit(c))
    {
        sourceCodeManager_->unget();
        token = createNumToken();
    }
    else if (isalpha(c))
    {
        sourceCodeManager_->unget();
        token = createAlphaToken();
    }
    else
    {
        /* @TODO - errors */
        ErrorLogger::getInstance().logError(std::make_pair<unsigned int, std::string>(static_cast<unsigned int &&> (lineNr_),
                                                          "Cannot resolve token starting from"));
        return nullptr;
    }
    c = sourceCodeManager_->getNext();
    if (!isDelimiter(c) && !iswspace(c))
    {
        /* @TODO - errors */
        ErrorLogger::getInstance().logError(std::make_pair<unsigned int, std::string> (static_cast<unsigned int &&> (lineNr_), "Cannot resolve token: 'token'"));
        return nullptr;
    }

    if (c == '\n')
        ++lineNr_;

    return token;
}

TokenPtr Scanner::createNumToken ()
{
    std::string token = "";
    char c = sourceCodeManager_->getNext();
    while (isdigit(c))
    {
        token += c;
        c = sourceCodeManager_->getNext();
    }

    sourceCodeManager_->unget();
    return std::make_shared<Token> (new NumericValue (std::stol(token)));
}

TokenPtr Scanner::createAlphaToken()
{
    char c = sourceCodeManager_->getNext();
    std::string token = "";
    int wordCounter = 1;
    TokenPtr result = nullptr;

    while (isdigit(c) || isalpha(c) || (c == '_'))
    {
        if (wordCounter > MAX_IDENTIFIER_LENGTH)
            ErrorLogger::getInstance().logError(std::make_pair<unsigned int, std::string> (static_cast<unsigned int &&> (lineNr_), "Too long identifier."));

        token += c;
        ++wordCounter;
        c = sourceCodeManager_->getNext();
    }
    if (result = RedcodeInterpreter::getInstance().isInstruction(token))
        return result;
    if (result = RedcodeInterpreter::getInstance().isModifier(token))
        return result;
    if (result = RedcodeInterpreter::getInstance().isPseudoInstr(token))
        return result;
    else
        result = std::make_shared<Token> (new Label (token));

    sourceCodeManager_->unget();
    return result;
}