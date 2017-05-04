//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_IDENTIFIER_HPP
#define REDCODEINTERPRETER_IDENTIFIER_HPP

#include "../Symbol.hpp"

class Identifier : Symbol
{
public:
    Identifier (RedcodeInterpreter::TokenType type) : Symbol(type)
    {}


};

typedef std::shared_ptr<Identifier> IdentifierPtr;

#endif //REDCODEINTERPRETER_IDENTIFIER_HPP
