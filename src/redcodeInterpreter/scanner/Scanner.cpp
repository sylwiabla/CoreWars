//
// Created by Sylwia Blach on 4/19/17.
//

#include "Scanner.hpp"

const std::map<char, int> Scanner::delimiters_ = {{',', 0}, {'.', 1}};

const std::string Scanner::getToken()
{
    do
        currentState_->handler_();
    while (!currentState_->isTerminal());

    StatePtr prevState = currentState_;
    currentState_->handler_();
    std::string result = prevState->getMessage();
    return result;
}

bool isDelimiter (const char & c)
{
    return Scanner::getInstance().delimiters_.find(c) != Scanner::getInstance().delimiters_.end();
}

void startStateHandler()
{
    char c;
    c = Scanner::getInstance().sourceCodeManager_->getNext();
    if (Scanner::getInstance().sourceCodeManager_->endReached())
        Scanner::getInstance().currentState_ = Scanner::getInstance().endState_;
    if (c == Scanner::getInstance().COMMENT_START)
        Scanner::getInstance().currentState_ = Scanner::getInstance().commentState_;
    else if (iswspace(c)) {
        Scanner::getInstance().currentState_ = Scanner::getInstance().wspaceState_;
        if (c == '\n')
            ++Scanner::getInstance().lineNr_;
    }
    else if (isDelimiter(c))
    {
        /** @TODO **/
        Scanner::getInstance().currentState_->setMessage("Unexpected delimiter");
    }
    else
        Scanner::getInstance().currentState_ = Scanner::getInstance().tokenState_;
}

void omitComment()
{
    char c;
    do
    {
        c = Scanner::getInstance().sourceCodeManager_->getNext();
        if (Scanner::getInstance().sourceCodeManager_->endReached())
        {
            Scanner::getInstance().currentState_ = Scanner::getInstance().endState_;
            return;
        }
    }
    while (c != '\n');

    ++Scanner::getInstance().lineNr_;
    Scanner::getInstance().currentState_ = Scanner::getInstance().startState_;
}

void omitWhiteSpaces()
{
    char c;
    do
    {
        c = Scanner::getInstance().sourceCodeManager_->getNext();
        if(Scanner::getInstance().sourceCodeManager_->endReached())
        {
            Scanner::getInstance().currentState_ = Scanner::getInstance().endState_;
            return;
        }
        if(c == '\n')
            ++Scanner::getInstance().lineNr_;
    }
    while (!iswspace(c));

    Scanner::getInstance().sourceCodeManager_->unget();
    Scanner::getInstance().currentState_ = Scanner::getInstance().startState_;
}

void logError()
{
    /** @TODO  **/
    Scanner::getInstance().currentState_->setMessage("Error: too long identifier name");
    Scanner::getInstance().currentState_ = Scanner::getInstance().startState_;
}

void logEOF()
{
    /** @TODO **/
    Scanner::getInstance().currentState_->setMessage("End of source file");
    Scanner::getInstance().currentState_ = Scanner::getInstance().startState_;
}

void createToken()
{
    std::string token = "";
    char c;
    unsigned int nrChars = 0;

    do
    {
        c = Scanner::getInstance().sourceCodeManager_->getNext();
        if(Scanner::getInstance().sourceCodeManager_->endReached())
        {
            Scanner::getInstance().currentState_ = Scanner::getInstance().endState_;
            if (token != "")
                Scanner::getInstance().currentState_->setMessage(token);
            return;
        }
        ++nrChars;

        if(nrChars > Scanner::getInstance().MAX_IDENTIFIER_LENGTH)
        {
            Scanner::getInstance().currentState_ = Scanner::getInstance().errorState_;
            return;
        }

        if (iswspace(c) || isDelimiter(c))
        {
            if (token != "")
                Scanner::getInstance().currentState_->setMessage(token);
            Scanner::getInstance().currentState_ = Scanner::getInstance().startState_;
            return;
        }
        else
        {
            token += c;
        }
    }
    while(1);
}