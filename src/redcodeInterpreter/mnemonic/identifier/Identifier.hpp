//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_IDENTIFIER_HPP
#define REDCODEINTERPRETER_IDENTIFIER_HPP

#include "../../Token.hpp"

class Identifier : public Token
{
public:
    Identifier ()
    {}

    Identifier (std::string name) : name_(name)
    {}

private:
    std::string name_;
};

typedef std::shared_ptr<Identifier> IdentifierPtr;

#endif //REDCODEINTERPRETER_IDENTIFIER_HPP
