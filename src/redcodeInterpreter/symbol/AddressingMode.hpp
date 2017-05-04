//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_ADDRESSINGMODE_HPP
#define REDCODEINTERPRETER_ADDRESSINGMODE_HPP

#include "Symbol.hpp"

class AddressingMode : public Symbol
{
public:
    AddressingMode (RedcodeInterpreter::TokenType type) : Symbol(type)
    {}


};

typedef std::shared_ptr<AddressingMode> AddrModePtr;

#endif //REDCODEINTERPRETER_ADDRESSINGMODE_HPP
