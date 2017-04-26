//
// Created by Sylwia Blach on 4/26/17.
//

#ifndef REDCODEINTERPRETER_REDCODEINTERPRETER_HPP
#define REDCODEINTERPRETER_REDCODEINTERPRETER_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "token/keyword/instruction/TwoArgsInstruction.hpp"
#include "token/keyword/instruction/OneArgsInstruction.hpp"
#include "token/keyword/instruction/ZeroArgsInstruction.hpp"
#include "token/keyword/AddressingMode.hpp"
#include "token/keyword/Modifier.hpp"
#include "token/keyword/PseudoInstruction.hpp"

class RedcodeInterpreter
{
public:
    static RedcodeInterpreter & getInstance()
    {
        static RedcodeInterpreter instance;
        return instance;
    }

    void init ();

    const TokenPtr & isInstruction (std::string name);
    const TokenPtr & isModifier (std::string name);
    const TokenPtr & isAddrMode (char name);
    const TokenPtr & isPseudoInstr (std::string name);

private:
    RedcodeInterpreter ()
    {}

    RedcodeInterpreter (RedcodeInterpreter const&) = delete;
    void operator=(RedcodeInterpreter const&) = delete;

    std::unordered_map<std::string, TwoArgsInstrPtr> twoArgsInstructions_;
    std::unordered_map<std::string, OneArgsInstrPtr> oneArgsInstructions_;
    std::unordered_map<std::string, ZeroArgsInstrPtr> zeroArgsInstructions_;
    std::unordered_map<std::string, ModifierPtr> modifiers_;
    std::unordered_map<char, AddrModePtr> addressingModes_;
    std::unordered_map<std::string, PseudoInstrPtr> pseudoInstructions_;
};

#endif //REDCODEINTERPRETER_REDCODEINTERPRETER_HPP
