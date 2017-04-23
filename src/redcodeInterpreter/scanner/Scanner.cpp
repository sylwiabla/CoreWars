//
// Created by Sylwia Blach on 4/19/17.
//

#include "Scanner.hpp"

const std::map<char, int> Scanner::delimiters_ = {{',', 0}, {'.', 1}};

std::string Scanner::getToken()
{
    do
        currentState_->handler_();
    while (!currentState_->isTerminal());

    StatePtr prevState = currentState_;
    currentState_->handler_();
    std::string result = prevState->getMessage();
    return result;
}

bool Scanner::isDelimiter (const char & c)
{
    return Scanner::getInstance().delimiters_.find(c) != Scanner::getInstance().delimiters_.end();
}

void Scanner::startStateHandler()
{
    char c;
    Scanner * scanner = &Scanner::getInstance();

    c = scanner->sourceCodeManager_->getNext();
    if (scanner->sourceCodeManager_->endReached())
        scanner->currentState_ = scanner->endState_;
    else if (c == scanner->COMMENT_START)
        scanner->currentState_ = scanner->commentState_;
    else if (iswspace(c))
    {
        scanner->currentState_ = scanner->wSpaceState_;
        if (c == '\n')
            ++scanner->lineNr_;
    }
    else if (isDelimiter(c))
    {
        unsigned int lineNr = Scanner::getInstance().lineNr_;
        ErrorLogger::getInstance().logError(std::make_pair<unsigned int, std::string> (static_cast<unsigned int &&> (lineNr), "Unexpected delimiter"));
    }
    else
    {
        scanner->sourceCodeManager_->unget();
        scanner->currentState_ = scanner->tokenState_;
    }
}

void Scanner::omitComment()
{
    char c;
    Scanner * scanner = &Scanner::getInstance();
    do
    {
        c = scanner->sourceCodeManager_->getNext();
        if (scanner->sourceCodeManager_->endReached())
        {
            scanner->currentState_ = scanner->endState_;
            return;
        }
    }
    while (c != '\n');

    ++(scanner->lineNr_);
    scanner->currentState_ = scanner->startState_;
}

void Scanner::omitWhiteSpaces()
{
    char c;
    Scanner * scanner = &Scanner::getInstance();
    do
    {
        c = scanner->sourceCodeManager_->getNext();
        if(scanner->sourceCodeManager_->endReached())
        {
            scanner->currentState_ = scanner->endState_;
            return;
        }
        if(c == '\n')
            ++scanner->lineNr_;
    }
    while (iswspace(c));

    scanner->sourceCodeManager_->unget();
    scanner->currentState_ = scanner->startState_;
}

void Scanner::logError()
{
    Scanner * scanner = &Scanner::getInstance();
    unsigned int lineNr = Scanner::getInstance().lineNr_;
    std::string message = scanner->currentState_->getMessage();
    ErrorLogger::getInstance().logError(std::make_pair<unsigned int, std::string> (static_cast<unsigned int &&> (lineNr), static_cast<std::string &&> (message)));
    scanner->currentState_ = scanner->startState_;
}

void Scanner::logEOF()
{
    Scanner * scanner = &Scanner::getInstance();
    scanner->currentState_->setMessage("EOF");
    scanner->currentState_ = scanner->startState_;
}

void Scanner::createToken()
{
    std::string token = "";
    char c;
    unsigned int nrChars = 0;
    Scanner * scanner = &Scanner::getInstance();

    do
    {
        c = scanner->sourceCodeManager_->getNext();
        if(scanner->sourceCodeManager_->endReached())
        {
            if (token != "")
                scanner->currentState_->setMessage(token);
            scanner->currentState_ = scanner->endState_;
            return;
        }
        ++nrChars;

        if(nrChars > scanner->MAX_IDENTIFIER_LENGTH)
        {
            scanner->currentState_ = scanner->errorState_;
            scanner->currentState_->setMessage("Too long identifier");
            return;
        }

        if (iswspace(c) || isDelimiter(c))
        {
            if (token != "")
                scanner->currentState_->setMessage(token);
            scanner->currentState_ = scanner->startState_;
            return;
        }
        else
        {
            token += c;
        }
    }
    while(1);
}