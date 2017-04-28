//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_IDENTIFIER_HPP
#define REDCODEINTERPRETER_IDENTIFIER_HPP

#include "../Mnemonic.hpp"

class Identifier : Mnemonic
{
public:
    Identifier (RedcodeInterpreter::TokenType type) : Mnemonic(type)
    {}


};

typedef std::shared_ptr<Identifier> IdentifierPtr;

#endif //REDCODEINTERPRETER_IDENTIFIER_HPP
