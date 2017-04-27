//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_TOKEN_HPP
#define REDCODEINTERPRETER_TOKEN_HPP

#include <memory>

class Token
{
public:
    Token()
    {}

    void greet ()
    {}

};

typedef std::shared_ptr<Token> TokenPtr;

#endif //REDCODEINTERPRETER_TOKEN_HPP
