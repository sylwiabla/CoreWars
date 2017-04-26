//
// Created by Sylwia Blach on 4/26/17.
//

#ifndef REDCODEINTERPRETER_TWOARGSINSTRUCTION_HPP
#define REDCODEINTERPRETER_TWOARGSINSTRUCTION_HPP

#include <tuple>
#include "Instruction.hpp"
#include "../AddressingMode.hpp"
#include "../../Identifier.hpp"
#include "../Modifier.hpp"

class TwoArgsInstruction : public Instruction
{
public:
    TwoArgsInstruction ()
    {}

private:
    std::tuple<AddrModePtr, IdentifierPtr, ModifierPtr> aArg;
    std::tuple<AddrModePtr, IdentifierPtr, ModifierPtr> bArg;
};

#endif //REDCODEINTERPRETER_TWOARGSINSTRUCTION_HPP
