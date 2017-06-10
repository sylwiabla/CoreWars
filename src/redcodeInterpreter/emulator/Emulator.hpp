//
// Created by sylwia on 6/7/17.
//

#ifndef REDCODEINTERPRETER_EMULATOR_HPP
#define REDCODEINTERPRETER_EMULATOR_HPP

#include <vector>
#include <list>
#include <atomic>
#include <unordered_map>
#include "../instruction/Instruction.hpp"
#include "Warrior.hpp"
#include "../parser/Parser.hpp"

typedef std::vector<InstructionPtr> Core;
typedef std::shared_ptr<Core> CorePtr;
typedef std::function<void (InstructionPtr)> RedcodeFunction;
typedef std::unordered_map<Token::TokenType, RedcodeFunction, std::EnumClassHash> RedcodeInstructionsSet;

class Emulator
{
private:
    unsigned long coreSize_;
    CorePtr core_;
    int nrInvoked_;

    WarriorPtr firstWarrior_;
    WarriorPtr secondWarrior_;
    bool firstCurrent_;

    std::atomic_int processIdGenerator_;

    static const RedcodeInstructionsSet functions_;

public:
    Emulator (unsigned long coreSize);

    void loadWarriors (CorePtr warrior1Code, CorePtr warrior2Code);
    void invokeInstruction ();

private:
    long findPCForSecond (long firstBegin, long firstEnd);
};

#endif //REDCODEINTERPRETER_EMULATOR_HPP
