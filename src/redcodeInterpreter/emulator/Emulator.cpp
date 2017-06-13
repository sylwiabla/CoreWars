//
// Created by sylwia on 6/8/17.
//

#include <algorithm>
#include <boost/random/mersenne_twister.hpp>
#include "Emulator.hpp"
#include "exceptions/OutOfMemory.hpp"

std::pair <long, long> Emulator::getAddresses (InstructionPtr instruction)
{
    OperandPtr aArg = instruction->getOperand(true);
    OperandPtr bArg = instruction->getOperand(false);

    Token::TokenType aAddrMode = std::get<0> (*aArg);
    Token::TokenType bAddrMode = std::get<0> (*bArg);

    return std::make_pair<long, long> (getAddress(aArg, aAddrMode), getAddress(bArg, bAddrMode));
}

long Emulator::getAddress (OperandPtr operand, Token::TokenType addrMode)
{
    long value = std::get <1> (*operand);
    if (addrMode == Token::end)
        return (value + pc_) % coreSize_;
    else if (addrMode == Token::directMode)
        return directGetter(value, pc_);
    else if (addrMode == Token::indirectMode)
        return indirectGetter(value, pc_);
    else if (addrMode == Token::immediateMode)
        return immediateGetter(value, pc_);
}

long Emulator::immediateGetter (long value, long pc)
{
    return  (pc + value) % coreSize_;
}

long Emulator::directGetter (long value, long pc)
{
    long temp = (pc + value) % coreSize_;
    OperandPtr tempOp = core_[temp]->getOperand(true);
    long tempAddr = std::get<1> (*tempOp);
    return (pc + tempAddr) % coreSize_;
}

long Emulator::indirectGetter (long value, long pc)
{
    long temp = (pc + value) % coreSize_;
    OperandPtr tempOpA = core_[temp]->getOperand(true);
    OperandPtr tempOpB = core_[temp]->getOperand(false);
    long tempBaseAddr = std::get<1> (*tempOpA);
    long tempOffset = std::get<1> (*tempOpB);
    return (pc + tempBaseAddr + tempOffset) % coreSize_;
}

void Emulator::aModHandler (long aOp, long bOp)
{
    InstructionPtr targetInstruction = core_[(pc_ + bOp) % coreSize_];
    InstructionPtr sourceInstruction = core_[(pc_ + aOp) % coreSize_];
    targetInstruction->setOperand (sourceInstruction->getOperand(true), true);
}

void Emulator::bModHandler (long aOp, long bOp)
{
    InstructionPtr targetInstruction = core_[(pc_ + bOp) % coreSize_];
    InstructionPtr sourceInstruction = core_[(pc_ + aOp) % coreSize_];
    targetInstruction->setOperand (sourceInstruction->getOperand(false), false);
}

void Emulator::abModHandler (long aOp, long bOp)
{
    InstructionPtr targetInstruction = core_[(pc_ + bOp) % coreSize_];
    InstructionPtr sourceInstruction = core_[(pc_ + aOp) % coreSize_];
    targetInstruction->setOperand (sourceInstruction->getOperand(true), false);
}

void Emulator::baModHandler (long aOp, long bOp)
{
    InstructionPtr targetInstruction = core_[(pc_ + bOp) % coreSize_];
    InstructionPtr sourceInstruction = core_[(pc_ + aOp) % coreSize_];
    targetInstruction->setOperand (sourceInstruction->getOperand(false), true);
    targetInstruction->setOperand (sourceInstruction->getOperand(false), true);
}

void Emulator::fModHandler (long aOp, long bOp)
{
    aModHandler(aOp, bOp);
}

void Emulator::xModHandler (long aOp, long bOp)
{
    abModHandler(aOp, bOp);
    baModHandler(aOp, bOp);
}

void Emulator::iModHandler (long aOp, long bOp)
{
    core_[(pc_ + bOp) % coreSize_] = core_[(pc_ + aOp) % coreSize_];
}

void Emulator::applyModifiers (InstructionPtr instruction)
{
    OperandPtr aArg = instruction->getOperand(true);
    OperandPtr bArg = instruction->getOperand(false);

    Token::TokenType aModifier = std::get<2> (*aArg);
    Token::TokenType bModifier = std::get<2> (*bArg);

    applyModifier (aArg, bArg, aModifier);
    applyModifier (aArg, bArg, bModifier);
}

void Emulator::applyModifier (OperandPtr operandA, OperandPtr operandB, Token::TokenType type)
{
    long aValue = std::get<1> (*operandA);
    long bValue = std::get<1> (*operandB);

    if (type == Token::AModifier)
        aModHandler(aValue, bValue);
    else if (type == Token::BModifier)
        bModHandler(aValue, bValue);
    else if (type == Token::ABModifier)
        abModHandler(aValue, bValue);
    else if (type == Token::FModifier)
        fModHandler(aValue, bValue);
    else if (type == Token::XModifier)
        xModHandler(aValue, bValue);
    else if (type == Token::IModifier)
        iModHandler(aValue, bValue);
}

Emulator::Emulator (unsigned long coreSize, int maxInvoked, InstructionPtr i) : pc_(0), nrInvoked_(0), coreSize_(coreSize), firstCurrent_(true),
                                                                                            core_(coreSize, i)//std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ()))
{
    maxInvoked_ = maxInvoked;

    processIdGenerator_ = 0;
    firstWarrior_ = std::make_shared<Warrior> (Warrior ());
    secondWarrior_ = std::make_shared<Warrior> (Warrior ());

    movFunctor = std::make_shared<MovFunctor>();
    datFunctor = std::make_shared<DatFunctor>();
    addFunctor = std::make_shared<AddFunctor>();
    subFunctor = std::make_shared<SubFunctor>();
    mulFunctor = std::make_shared<MulFunctor>();
    divFunctor = std::make_shared<DivFunctor>();
    modFunctor = std::make_shared<ModFunctor>();
    jmzFunctor = std::make_shared<JmzFunctor>();
    jmnFunctor = std::make_shared<JmnFunctor>();
    djnFunctor = std::make_shared<DjnFunctor>();
    splFunctor = std::make_shared<SplFunctor>();
    cmpFunctor = std::make_shared<CmpFunctor>();
    seqFunctor = std::make_shared<SeqFunctor>();
    sneFunctor = std::make_shared<SneFunctor>();
    sltFunctor = std::make_shared<SltFunctor>();
    jmpFunctor = std::make_shared<JmpFunctor>();
    nopFunctor = std::make_shared<NopFunctor>();

    functors_ = {{Token::mov, movFunctor}, {Token::dat, datFunctor}, {Token::add, addFunctor},
                 {Token::sub, subFunctor}, {Token::mul, mulFunctor}, {Token::div, divFunctor},
                 {Token::mod, modFunctor}, {Token::jmz, jmzFunctor}, {Token::jmn, jmnFunctor},
                 {Token::djn, djnFunctor}, {Token::spl, splFunctor}, {Token::cmp, cmpFunctor},
                 {Token::seq, seqFunctor}, {Token::sne, sneFunctor}, {Token::slt, sltFunctor},
                 {Token::jmp, jmpFunctor}, {Token::nop, nopFunctor}};
}

void Emulator::loadWarriors (CodePtr warrior1Code, CodePtr warrior2Code)
{
    long nrInstrFirst = 0;
    std::for_each (warrior1Code->begin(), warrior1Code->end(), [&nrInstrFirst] (InstructionPtr instruction)
                    {nrInstrFirst += instruction->getNrInstructions();}
    );
    long nrInstrSecond = 0;
    std::for_each (warrior2Code->begin(), warrior2Code->end(), [&nrInstrSecond] (InstructionPtr instruction)
                   {nrInstrSecond += instruction->getNrInstructions();}
    );

    if ((nrInstrFirst + nrInstrSecond) > coreSize_)
        throw new OutOfMemory ();

    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<long> distr;
    long firstPC = distr(eng) % coreSize_;
    firstWarrior_->createProcess(processIdGenerator_++, firstPC);
    long i = firstPC;
    std::for_each(warrior1Code->begin(), warrior1Code->end(), [this, &i] (InstructionPtr outerInst) {
        i = outerInst->getInstructions(core_, i % coreSize_, coreSize_);
    });

    long secondPC = findPCForSecond(firstPC, nrInstrFirst, nrInstrSecond);
    secondWarrior_->createProcess(processIdGenerator_++, secondPC);
    long j = secondPC;
    std::for_each(warrior2Code->begin(), warrior2Code->end(), [this, &j] (InstructionPtr outerInst) {
        j = outerInst->getInstructions(core_, j, coreSize_);
    });

    pc_ = firstPC;
}

Emulator::Winner Emulator::invokeInstruction ()
{
    if (nrInvoked_ > maxInvoked_)
        return NONE;
    WarriorPtr current = (firstCurrent_ ? firstWarrior_ : secondWarrior_);
    pc_ = current->getPC();

    InstructionPtr instruction = core_[pc_];
    Token::TokenType type = instruction->getType();
    FunctorPtr functor = functors_.find(type)->second;
    if (!(*functor)(*this, instruction))
        return firstCurrent_ ? SECOND : FIRST;

    current->switchProcess();
    firstCurrent_ = !firstCurrent_;
    ++nrInvoked_;
    return WAITING;
}

long Emulator::findPCForSecond (long firstBegin, long nrInstrFirst, long nrInstrSecond)
{
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<long> distr;
    long pc = distr(eng) % (coreSize_ - nrInstrFirst - nrInstrSecond);

    if ((firstBegin + nrInstrFirst) >= coreSize_)
        pc += nrInstrFirst - coreSize_ + firstBegin;
    else
        pc += firstBegin + nrInstrFirst;

    return pc;
}

bool Emulator::MovFunctor::operator () (Emulator & e, InstructionPtr i)
{
    auto addresses = e.getAddresses (i);
    InstructionPtr source = e.getMemoryCell(addresses.first);
    e.setMemoryCell(source, addresses.second);
    e.applyModifiers(i);
}

bool Emulator::DatFunctor::operator () (Emulator & e, InstructionPtr i)
{
    bool stillRunning = e.killProcess();
    e.applyModifiers(i);
    return stillRunning;
}

bool Emulator::AddFunctor::operator () (Emulator & e, InstructionPtr i)
{
    auto addresses = e.getAddresses (i);
    e.setMemoryCell((addresses.first + addresses.second) % e.getCoreSize(), e.getPc(), true);
    e.applyModifiers(i);
}

bool Emulator::SubFunctor::operator () (Emulator & e, InstructionPtr i)
{
    auto addresses = e.getAddresses (i);
    e.setMemoryCell((addresses.first - addresses.second) % e.getCoreSize(), e.getPc(), true);
    e.applyModifiers(i);
}

bool Emulator::MulFunctor::operator () (Emulator & e, InstructionPtr i)
{
    auto addresses = e.getAddresses (i);
    e.setMemoryCell((addresses.first * addresses.second) % e.getCoreSize(), e.getPc(), true);
    e.applyModifiers(i);
}

bool Emulator::DivFunctor::operator () (Emulator & e, InstructionPtr i)
{
    auto addresses = e.getAddresses (i);
    e.setMemoryCell((addresses.first / addresses.second) % e.getCoreSize(), e.getPc(), true);
    e.applyModifiers(i);
}

bool Emulator::ModFunctor::operator () (Emulator & e, InstructionPtr i)
{
    auto addresses = e.getAddresses (i);
    e.setMemoryCell((addresses.first % addresses.second) % e.getCoreSize(), e.getPc(), true);
    e.applyModifiers(i);
}

bool Emulator::JmzFunctor::operator () (Emulator & e, InstructionPtr i)
{
    auto addresses = e.getAddresses (i);
    if (!addresses.second)
        e.jump(addresses.first);
    e.applyModifiers(i);
}

bool Emulator::JmnFunctor::operator () (Emulator & e, InstructionPtr i)
{
    auto addresses = e.getAddresses (i);
    if (addresses.second)
        e.jump(addresses.first);
    e.applyModifiers(i);
}

bool Emulator::DjnFunctor::operator () (Emulator & e, InstructionPtr i)
{
    auto addresses = e.getAddresses (i);
    e.setMemoryCell(addresses.second - 1, e.getPc(), false);
    if (!(addresses.second - 1))
        e.jump(addresses.first);
    e.applyModifiers(i);
}

bool Emulator::SplFunctor::operator () (Emulator & e, InstructionPtr i)
{
    auto addresses = e.getAddresses (i);
    e.createProcess(addresses.first);
    e.applyModifiers(i);
}

bool Emulator::CmpFunctor::operator () (Emulator & e, InstructionPtr i)
{
    auto addresses = e.getAddresses (i);
    if (addresses.first == addresses.second)
        e.jump(e.getPc() + 1);
    e.applyModifiers(i);
}

bool Emulator::SeqFunctor::operator () (Emulator & e, InstructionPtr i)
{
    auto addresses = e.getAddresses (i);
    if (addresses.first == addresses.second)
        e.jump(e.getPc() + 1);
    e.applyModifiers(i);
}

bool Emulator::SneFunctor::operator () (Emulator & e, InstructionPtr i)
{
    auto addresses = e.getAddresses (i);
    if (addresses.first != addresses.second)
        e.jump(e.getPc() + 1);
    e.applyModifiers(i);
}

bool Emulator::SltFunctor::operator () (Emulator & e, InstructionPtr i)
{
    auto addresses = e.getAddresses (i);
    if (addresses.first < addresses.second)
        e.jump(e.getPc() + 1);
    e.applyModifiers(i);
}

bool Emulator::JmpFunctor::operator () (Emulator & e, InstructionPtr i)
{
    auto addresses = e.getAddresses (i);
    e.jump(addresses.first);
    e.applyModifiers(i);
}