//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_INSTRUCTION_HPP
#define REDCODEINTERPRETER_INSTRUCTION_HPP

#include "../Symbol.hpp"

class Instruction : public Symbol
{
public:
    Instruction (RedcodeInterpreter::TokenType type) : Symbol(type)
    {}


};

typedef std::shared_ptr<Instruction> InstructionPtr;

#endif //REDCODEINTERPRETER_INSTRUCTION_HPP
