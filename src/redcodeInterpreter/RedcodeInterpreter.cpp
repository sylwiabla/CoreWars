//
// Created by Sylwia Blach on 4/26/17.
//

#include "RedcodeInterpreter.hpp"

template<> TokenPtr RedcodeInterpreter::isKeyword<char, AddrModePtr> (char name, std::unordered_map<char, AddrModePtr> map);
template<> TokenPtr RedcodeInterpreter::isKeyword<std::string, ModifierPtr> (std::string name, std::unordered_map<std::string, ModifierPtr> map);
template<> TokenPtr RedcodeInterpreter::isKeyword<std::string, PseudoInstrPtr> (std::string name, std::unordered_map<std::string, PseudoInstrPtr> map);
template<> TokenPtr RedcodeInterpreter::isKeyword<std::string, TwoArgsInstrPtr> (std::string name, std::unordered_map<std::string, TwoArgsInstrPtr> map);
template<> TokenPtr RedcodeInterpreter::isKeyword<std::string, OneArgsInstrPtr> (std::string name, std::unordered_map<std::string, OneArgsInstrPtr> map);
template<> TokenPtr RedcodeInterpreter::isKeyword<std::string, ZeroArgsInstrPtr> (std::string name, std::unordered_map<std::string, ZeroArgsInstrPtr> map);

void RedcodeInterpreter::init()
{
    addressingModes_.insert(std::make_pair<char, AddrModePtr> ('#', std::make_shared<AddressingMode> (AddressingMode ('#'))));
    addressingModes_.insert(std::make_pair<char, AddrModePtr> ('$', std::make_shared<AddressingMode> (AddressingMode ('$'))));
    addressingModes_.insert(std::make_pair<char, AddrModePtr> ('@', std::make_shared<AddressingMode> (AddressingMode ('@'))));

    modifiers_.insert(std::make_pair<std::string, ModifierPtr> ("A", std::make_shared<Modifier> (Modifier ("A"))));
    modifiers_.insert(std::make_pair<std::string, ModifierPtr> ("B", std::make_shared<Modifier> (Modifier ("B"))));
    modifiers_.insert(std::make_pair<std::string, ModifierPtr> ("AB", std::make_shared<Modifier> (Modifier ("AB"))));
    modifiers_.insert(std::make_pair<std::string, ModifierPtr> ("BA", std::make_shared<Modifier> (Modifier ("BA"))));
    modifiers_.insert(std::make_pair<std::string, ModifierPtr> ("F", std::make_shared<Modifier> (Modifier ("F"))));
    modifiers_.insert(std::make_pair<std::string, ModifierPtr> ("X", std::make_shared<Modifier> (Modifier ("X"))));
    modifiers_.insert(std::make_pair<std::string, ModifierPtr> ("I", std::make_shared<Modifier> (Modifier ("I"))));

    pseudoInstructions_.insert(std::make_pair<std::string, PseudoInstrPtr> ("equ", std::make_shared<PseudoInstruction> (PseudoInstruction ("equ"))));
    pseudoInstructions_.insert(std::make_pair<std::string, PseudoInstrPtr> ("org", std::make_shared<PseudoInstruction> (PseudoInstruction ("org"))));
    pseudoInstructions_.insert(std::make_pair<std::string, PseudoInstrPtr> ("end", std::make_shared<PseudoInstruction> (PseudoInstruction ("end"))));
    pseudoInstructions_.insert(std::make_pair<std::string, PseudoInstrPtr> ("for", std::make_shared<PseudoInstruction> (PseudoInstruction ("for"))));
    pseudoInstructions_.insert(std::make_pair<std::string, PseudoInstrPtr> ("rof", std::make_shared<PseudoInstruction> (PseudoInstruction ("rof"))));
    pseudoInstructions_.insert(std::make_pair<std::string, PseudoInstrPtr> ("pin", std::make_shared<PseudoInstruction> (PseudoInstruction ("pin"))));

    twoArgsInstructions_.insert(std::make_pair<std::string, TwoArgsInstrPtr> ("dat", std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ("dat", false))));
    twoArgsInstructions_.insert(std::make_pair<std::string, TwoArgsInstrPtr> ("mov", std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ("mov", false))));
    twoArgsInstructions_.insert(std::make_pair<std::string, TwoArgsInstrPtr> ("add", std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ("add", false))));
    twoArgsInstructions_.insert(std::make_pair<std::string, TwoArgsInstrPtr> ("sub", std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ("sub", false))));
    twoArgsInstructions_.insert(std::make_pair<std::string, TwoArgsInstrPtr> ("mul", std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ("mul", false))));
    twoArgsInstructions_.insert(std::make_pair<std::string, TwoArgsInstrPtr> ("div", std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ("div", false))));
    twoArgsInstructions_.insert(std::make_pair<std::string, TwoArgsInstrPtr> ("mod", std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ("mod", false))));
    twoArgsInstructions_.insert(std::make_pair<std::string, TwoArgsInstrPtr> ("jmz", std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ("jmz", false))));
    twoArgsInstructions_.insert(std::make_pair<std::string, TwoArgsInstrPtr> ("jmn", std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ("jmn", false))));
    twoArgsInstructions_.insert(std::make_pair<std::string, TwoArgsInstrPtr> ("djn", std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ("djn", false))));
    twoArgsInstructions_.insert(std::make_pair<std::string, TwoArgsInstrPtr> ("spl", std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ("spl", false))));
    twoArgsInstructions_.insert(std::make_pair<std::string, TwoArgsInstrPtr> ("cmp", std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ("cmp", false))));
    twoArgsInstructions_.insert(std::make_pair<std::string, TwoArgsInstrPtr> ("seq", std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ("seq", false))));
    twoArgsInstructions_.insert(std::make_pair<std::string, TwoArgsInstrPtr> ("sne", std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ("sne", false))));
    twoArgsInstructions_.insert(std::make_pair<std::string, TwoArgsInstrPtr> ("slt", std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ("slt", false))));
    twoArgsInstructions_.insert(std::make_pair<std::string, TwoArgsInstrPtr> ("ldp", std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ("ldp", false))));
    twoArgsInstructions_.insert(std::make_pair<std::string, TwoArgsInstrPtr> ("stp", std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ("stp", false))));

    oneArgsInstructions_.insert(std::make_pair<std::string, OneArgsInstrPtr> ("jmp", std::make_shared<OneArgsInstruction> (OneArgsInstruction ("jmp"))));

    zeroArgsInstructions_.insert(std::make_pair<std::string, ZeroArgsInstrPtr> ("nop", std::make_shared<ZeroArgsInstruction> (ZeroArgsInstruction ("nop"))));
}

TokenPtr RedcodeInterpreter::isInstruction (std::string name)
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

TokenPtr RedcodeInterpreter::isModifier (std::string name)
{
    return isKeyword<std::string, ModifierPtr>(name, modifiers_);
}

TokenPtr RedcodeInterpreter::isAddrMode (char name)
{
    return isKeyword<char, AddrModePtr>(name, addressingModes_);
}

TokenPtr RedcodeInterpreter::isPseudoInstr (std::string name)
{
    return isKeyword<std::string, PseudoInstrPtr>(name, pseudoInstructions_);
}