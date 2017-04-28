//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_INSTRUCTION_HPP
#define REDCODEINTERPRETER_INSTRUCTION_HPP

#include "../Mnemonic.hpp"

class Instruction : public Mnemonic
{
public:
    Instruction (RedcodeInterpreter::TokenType type) : Mnemonic(type)
    {}


};

typedef std::shared_ptr<Instruction> InstructionPtr;

#endif //REDCODEINTERPRETER_INSTRUCTION_HPP
