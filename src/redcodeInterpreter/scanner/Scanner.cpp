//
// Created by Sylwia Blach on 4/19/17.
//

#include "Scanner.hpp"

static const std::map<char, int> delimiters_ = {{',', 0}, {'.', 1}};

const std::string & Scanner::getToken()
{
    do
        currentState_->handler_();
    while (!currentState_->isTerminal());

    StatePtr prevState = currentState_;
    currentState_->handler_();
    return prevState->getMessage();
}

bool Scanner::isDelimiter (const char & c)
{
    return delimiters_.find(c) == delimiters_.end();
}

void Scanner::startStateHandler()
{
    char c;
    c = sourceCodeManager_->getNext();
    if (sourceCodeManager_->endReached())
        currentState_ = endState_;
    if (c == COMMENT_START)
        currentState_ = commentState_;
    else if (iswspace(c)) {
        currentState_ = wspaceState_;
        if (c == '\n')
            ++lineNr_;
    }
    else if (isDelimiter(c))
    {
        /** @TODO **/
        currentState_->setMessage("Unexpected delimiter");
    }
    else
        currentState_ = tokenState_;
}

void Scanner::omitComment()
{
    char c;
    do
    {
        c = sourceCodeManager_->getNext();
        if (sourceCodeManager_->endReached())
        {
            currentState_ = endState_;
            return;
        }
    }
    while (c != '\n');

    ++lineNr_;
    currentState_ = startState_;
}

void Scanner::omitWhiteSpaces()
{
    char c;
    do
    {
        c = sourceCodeManager_->getNext();
        if(sourceCodeManager_->endReached())
        {
            currentState_ = endState_;
            return;
        }
        if(c == '\n')
            ++lineNr_;
    }
    while (!iswspace(c));

    sourceCodeManager_->unget();
    currentState_ = startState_;
}

void Scanner::logError()
{
    /** @TODO  **/
    currentState_->setMessage("Error: too long identifier name");
    currentState_ = startState_;
}

void Scanner::logEOF()
{
    /** @TODO **/
    currentState_->setMessage("End of source file");
    currentState_ = startState_;
}

void Scanner::createToken()
{
    std::string token = "";
    char c;
    unsigned int nrChars = 0;

    do
    {
        c = sourceCodeManager_->getNext();
        if(sourceCodeManager_->endReached())
        {
            currentState_ = endState_;
            if (token != "")
                currentState_->setMessage(token);
            return;
        }
        ++nrChars;

        if(nrChars > MAX_IDENTIFIER_LENGTH)
        {
            currentState_ = errorState_;
            return;
        }

        if (iswspace(c) || isDelimiter(c))
        {
            if (token != "")
                currentState_->setMessage(token);
            currentState_ = startState_;
            return;
        }
        else
        {
            token += c;
        }
    }
    while(1);
}