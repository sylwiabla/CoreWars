//
// Created by Sylwia Blach on 4/26/17.
//

#ifndef REDCODEINTERPRETER_ONEARGSINSTRUCTION_HPP
#define REDCODEINTERPRETER_ONEARGSINSTRUCTION_HPP

#include "Instruction.hpp"
#include "../AddressingMode.hpp"
#include "../identifier/Identifier.hpp"
#include "../Modifier.hpp"

class OneArgsInstruction : public Instruction
{
public:
    OneArgsInstruction (std::string name) : Instruction (name)
    {}

private:
    std::tuple<AddrModePtr, IdentifierPtr, ModifierPtr> aArg;

};

typedef std::shared_ptr<OneArgsInstruction> OneArgsInstrPtr;

#endif //REDCODEINTERPRETER_ONEARGSINSTRUCTION_HPP
