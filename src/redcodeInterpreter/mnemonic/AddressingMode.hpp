//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_ADDRESSINGMODE_HPP
#define REDCODEINTERPRETER_ADDRESSINGMODE_HPP

#include "Mnemonic.hpp"

class AddressingMode : public Mnemonic
{
public:
    AddressingMode (RedcodeInterpreter::TokenType type) : Mnemonic(type)
    {}


};

typedef std::shared_ptr<AddressingMode> AddrModePtr;

#endif //REDCODEINTERPRETER_ADDRESSINGMODE_HPP
