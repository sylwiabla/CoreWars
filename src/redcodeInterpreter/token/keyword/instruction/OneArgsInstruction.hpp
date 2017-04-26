//
// Created by Sylwia Blach on 4/26/17.
//

#ifndef REDCODEINTERPRETER_ONEARGSINSTRUCTION_HPP
#define REDCODEINTERPRETER_ONEARGSINSTRUCTION_HPP

#include "Instruction.hpp"
#include "../AddressingMode.hpp"
#include "../../Identifier.hpp"
#include "../Modifier.hpp"

class OneArgsInstruction : public Instruction
{
public:
    OneArgsInstruction ()
    {}

private:
    std::tuple<AddrModePtr, IdentifierPtr, ModifierPtr> aArg;
};

#endif //REDCODEINTERPRETER_ONEARGSINSTRUCTION_HPP
