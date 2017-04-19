//
// Created by Sylwia Blach on 4/19/17.
//

#include "Scanner.hpp"

static const std::map<char, int> delimiters = {{',', 0}, {'.', 1}};

std::string Scanner::getToken()
{
    unsigned int nrChars = 0;
    std::string token = "";
    char c = '\0';

    while (nrChars <= MAX_IDENTIFIER_LENGTH)
    {
        c = sourceCodeManager_->getNext();

    }
}