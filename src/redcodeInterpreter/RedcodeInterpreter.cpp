//
// Created by Sylwia Blach on 4/26/17.
//

#include "RedcodeInterpreter.hpp"

const TokenPtr & RedcodeInterpreter::isKeyword<char, AddrModePtr> (char name, std::unordered_map<char, AddrModePtr> map);

void RedcodeInterpreter::init()
{
    addressingModes_.insert(std::make_shared<AddressingMode> (new AddressingMode ('#')));
    addressingModes_.insert(std::make_shared<AddressingMode> (new AddressingMode ('$')));
    addressingModes_.insert(std::make_shared<AddressingMode> (new AddressingMode ('@')));

    modifiers_.insert(std::make_shared<Modifier> (new Modifier ("A")));
    modifiers_.insert(std::make_shared<Modifier> (new Modifier ("B")));
    modifiers_.insert(std::make_shared<Modifier> (new Modifier ("AB")));
    modifiers_.insert(std::make_shared<Modifier> (new Modifier ("BA")));
    modifiers_.insert(std::make_shared<Modifier> (new Modifier ("F")));
    modifiers_.insert(std::make_shared<Modifier> (new Modifier ("X")));
    modifiers_.insert(std::make_shared<Modifier> (new Modifier ("I")));

    pseudoInstructions_.insert(std::make_shared<PseudoInstruction> (new PseudoInstruction ("equ")));
    pseudoInstructions_.insert(std::make_shared<PseudoInstruction> (new PseudoInstruction ("org")));
    pseudoInstructions_.insert(std::make_shared<PseudoInstruction> (new PseudoInstruction ("end")));
    pseudoInstructions_.insert(std::make_shared<PseudoInstruction> (new PseudoInstruction ("for")));
    pseudoInstructions_.insert(std::make_shared<PseudoInstruction> (new PseudoInstruction ("rof")));
    pseudoInstructions_.insert(std::make_shared<PseudoInstruction> (new PseudoInstruction ("pin")));

    twoArgsInstructions_.insert(std::make_shared<TwoArgsInstruction> (new TwoArgsInstruction ("dat", false)));
    twoArgsInstructions_.insert(std::make_shared<TwoArgsInstruction> (new TwoArgsInstruction ("mov", true)));
    twoArgsInstructions_.insert(std::make_shared<TwoArgsInstruction> (new TwoArgsInstruction ("add", true)));
    twoArgsInstructions_.insert(std::make_shared<TwoArgsInstruction> (new TwoArgsInstruction ("sub", true)));
    twoArgsInstructions_.insert(std::make_shared<TwoArgsInstruction> (new TwoArgsInstruction ("mul", true)));
    twoArgsInstructions_.insert(std::make_shared<TwoArgsInstruction> (new TwoArgsInstruction ("div", true)));
    twoArgsInstructions_.insert(std::make_shared<TwoArgsInstruction> (new TwoArgsInstruction ("mod", true)));
    twoArgsInstructions_.insert(std::make_shared<TwoArgsInstruction> (new TwoArgsInstruction ("jmz", true)));
    twoArgsInstructions_.insert(std::make_shared<TwoArgsInstruction> (new TwoArgsInstruction ("jmn", true)));
    twoArgsInstructions_.insert(std::make_shared<TwoArgsInstruction> (new TwoArgsInstruction ("djn", true)));
    twoArgsInstructions_.insert(std::make_shared<TwoArgsInstruction> (new TwoArgsInstruction ("spl", true)));
    twoArgsInstructions_.insert(std::make_shared<TwoArgsInstruction> (new TwoArgsInstruction ("cmp", true)));
    twoArgsInstructions_.insert(std::make_shared<TwoArgsInstruction> (new TwoArgsInstruction ("seq", true)));
    twoArgsInstructions_.insert(std::make_shared<TwoArgsInstruction> (new TwoArgsInstruction ("sne", true)));
    twoArgsInstructions_.insert(std::make_shared<TwoArgsInstruction> (new TwoArgsInstruction ("slt", true)));
    twoArgsInstructions_.insert(std::make_shared<TwoArgsInstruction> (new TwoArgsInstruction ("ldp", true)));
    twoArgsInstructions_.insert(std::make_shared<TwoArgsInstruction> (new TwoArgsInstruction ("stp", true)));

    oneArgsInstructions_.insert(std::make_shared<OneArgsInstruction> (new OneArgsInstruction ("jmp")));

    zeroArgsInstructions_.insert(std::make_shared<ZeroArgsInstruction> (new ZeroArgsInstruction ("nop")));
}

const TokenPtr & RedcodeInterpreter::isInstruction (std::string name)
{
    TokenPtr result = isKeyword<std::string, TwoArgsInstrPtr>(name, twoArgsInstructions_);
    if (!result)
        return result;

    result = isKeyword<std::string, OneArgsInstrPtr>(name, oneArgsInstructions_);
    if (!result)
        return result;

    result = isKeyword<std::string, ZeroArgsInstrPtr>(name, zeroArgsInstructions_);
    return result;
}

const TokenPtr & RedcodeInterpreter::isModifier (std::string name)
{
    return isKeyword<std::string, ModifierPtr>(name, modifiers_);
}

const TokenPtr & RedcodeInterpreter::isAddrMode (char name)
{
    return isKeyword<char, AddrModePtr>(name, addressingModes_);
}

const TokenPtr & RedcodeInterpreter::isPseudoInstr (std::string name)
{
    return isKeyword<std::string, PseudoInstrPtr>(name, pseudoInstructions_);
}