//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_TOKEN_HPP
#define REDCODEINTERPRETER_TOKEN_HPP

#include <memory>
#include "../RedcodeInterpreter.hpp"

class Token
{
public:
    Token(RedcodeInterpreter::TokenType type) : type_(type)
    {}

    Token (RedcodeInterpreter::TokenType type, std::string name) : type_(type), name_(name)
    {}

private:
    RedcodeInterpreter::TokenType type_;
    std::string name_;

};

typedef std::shared_ptr<Token> TokenPtr;

#endif //REDCODEINTERPRETER_TOKEN_HPP
