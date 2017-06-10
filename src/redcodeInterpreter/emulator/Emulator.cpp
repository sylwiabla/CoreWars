//
// Created by sylwia on 6/8/17.
//

#include <algorithm>
#include <boost/random/mersenne_twister.hpp>
#include "Emulator.hpp"
#include "exceptions/OutOfMemory.hpp"

const RedcodeInstructionsSet Emulator::functions_ = {};

Emulator::Emulator (unsigned long coreSize) : coreSize_(coreSize), nrInvoked_(0), firstCurrent_(true)
{
    core_ = std::make_shared<Core> (Core ());
    core_->reserve(coreSize);
    processIdGenerator_ = 0;

    firstWarrior_ = std::make_shared<Warrior> (Warrior ());
    secondWarrior_ = std::make_shared<Warrior> (Warrior ());
}

void Emulator::loadWarriors (CorePtr warrior1Code, CorePtr warrior2Code)
{
    long nrInstrFirst = warrior1Code->size();
    long nrInstrSecond = warrior2Code->size();

    if ((nrInstrFirst + nrInstrSecond) < coreSize_)
        throw new OutOfMemory ();

    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<long> distr;

    long firstPC = distr(eng) % coreSize_;
    firstWarrior_->createProcess(processIdGenerator_++, firstPC);
    long i = firstPC;
    std::for_each(warrior1Code->begin(), warrior1Code->end(), [this, &i] (InstructionPtr inst) {(*core_)[i++] = inst;});

    long secondPC = findPCForSecond(firstPC, firstPC + warrior1Code->size());
    secondWarrior_->createProcess(processIdGenerator_++, secondPC);
    long j = secondPC;
    std::for_each(warrior2Code->begin(), warrior2Code->end(), [this, &j] (InstructionPtr inst) {(*core_)[j++] = inst;});
}

void Emulator::invokeInstruction ()
{
    WarriorPtr current = (firstCurrent_ ? firstWarrior_ : secondWarrior_);
    long currentPC = current->getPC();

    InstructionPtr instruction = (*core_)[currentPC];
    Token::TokenType type = instruction->getType();
    RedcodeFunction function = functions_.at(type);
    function(instruction);

    current->switchProcess();
    firstCurrent_ = !firstCurrent_;
    ++nrInvoked_;
}

long Emulator::findPCForSecond (long firstBegin, long firstEnd)
{
    // @TODO
    return 1;
}