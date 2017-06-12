//
// Created by sylwia on 6/8/17.
//

#include <algorithm>
#include <boost/random/mersenne_twister.hpp>
#include "Emulator.hpp"
#include "exceptions/OutOfMemory.hpp"

void Emulator::init ()
{
    functions_.insert(std::make_pair(Token::mov, &Emulator::movFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::datFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::addFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::subFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::mulFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::divFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::modFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::jmzFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::jmnFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::djnFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::splFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::cmpFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::seqFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::sneFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::sltFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::ldpFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::stpFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::jmpFunction));
    functions_.insert(std::make_pair(Token::mov, &Emulator::nopFunction));

    addrModesMapping_.insert(std::make_pair(Token::immidiateMode, &Emulator::immidateGetter));
    addrModesMapping_.insert(std::make_pair(Token::directMode, &Emulator::directGetter));
    addrModesMapping_.insert(std::make_pair(Token::indirectMode, &Emulator::indirectGetter));

    modifierMapping_.insert((std::make_pair(Token::AModifier, &Emulator::aModHandler)));
    modifierMapping_.insert((std::make_pair(Token::BModifier, &Emulator::bModHandler)));
    modifierMapping_.insert((std::make_pair(Token::ABModifier, &Emulator::abModHandler)));
    modifierMapping_.insert((std::make_pair(Token::BAModifier, &Emulator::baModHandler)));
    modifierMapping_.insert((std::make_pair(Token::FModifier, &Emulator::fModHandler)));
    modifierMapping_.insert((std::make_pair(Token::XModifier, &Emulator::xModHandler)));
    modifierMapping_.insert((std::make_pair(Token::IModifier,&Emulator::iModHandler)));
}

std::pair <long, long> Emulator::getAddresses (InstructionPtr instruction)
{
    OperandPtr aArg = instruction->getOperand(true);
    OperandPtr bArg = instruction->getOperand(false);

    Token::TokenType aAddrMode = std::get<0> (*aArg);
    auto mapperA = &addrModesMapping_.at(aAddrMode);

    Token::TokenType bAddrMode = std::get<0> (*bArg);
    auto mapperB = &Emulator::addrModesMapping_.at(bAddrMode);

    return std::make_pair<long, long> ((aAddrMode == Token::end) ? std::get<1> (*aArg) : boost::bind (&mapperA, this, std::get<1> (*aArg), pc_),
                                       (bAddrMode == Token::end) ? std::get<1> (*bArg) : boost::bind (&mapperB, this, std::get<1> (*bArg), pc_);
}

bool Emulator::movFunction (InstructionPtr instruction)
{
    auto addresses = getAddresses (instruction);
    (*core_)[addresses.second] = (*core_)[addresses.first];
    applyModifier(instruction);
}

bool Emulator::datFunction (InstructionPtr instruction);
bool Emulator::addFunction (InstructionPtr instruction);
bool Emulator::subFunction (InstructionPtr instruction);
bool Emulator::mulFunction (InstructionPtr instruction);
bool Emulator::divFunction (InstructionPtr instruction);
bool Emulator::modFunction (InstructionPtr instruction);
bool Emulator::jmzFunction (InstructionPtr instruction);
bool Emulator::jmnFunction (InstructionPtr instruction);
bool Emulator::djnFunction (InstructionPtr instruction);
bool Emulator::splFunction (InstructionPtr instruction);
bool Emulator::cmpFunction (InstructionPtr instruction);
bool Emulator::seqFunction (InstructionPtr instruction);
bool Emulator::sneFunction (InstructionPtr instruction);
bool Emulator::sltFunction (InstructionPtr instruction);
bool Emulator::ldpFunction (InstructionPtr instruction);
bool Emulator::stpFunction (InstructionPtr instruction);
bool Emulator::jmpFunction (InstructionPtr instruction);

bool Emulator::nopFunction (InstructionPtr instruction)
{}

long Emulator::immidateGetter (long value, long pc)
{
    return  (pc + value) % coreSize_;
}

long Emulator::directGetter (long value, long pc)
{
    long temp = (pc + value) % coreSize_;
    OperandPtr tempOp = (*core_)[temp]->getOperand(true);
    long tempAddr = std::get<1> (*tempOp);
    return (pc + tempAddr) % coreSize_;
}

long Emulator::indirectGetter (long value, long pc)
{
    long temp = (pc + value) % coreSize_;
    OperandPtr tempOpA = (*core_)[temp]->getOperand(true);
    OperandPtr tempOpB = (*core_)[temp]->getOperand(false);
    long tempBaseAddr = std::get<1> (*tempOpA);
    long tempOffset = std::get<1> (*tempOpB);
    return (pc + tempBaseAddr + tempOffset) % coreSize_;
}

void Emulator::aModHandler (long aOp, long bOp)
{
    InstructionPtr targetInstruction = (*core_)[(pc_ + bOp) % coreSize_];
    InstructionPtr sourceInstruction = (*core_)[(pc_ + aOp) % coreSize_];
    targetInstruction->setOperand (sourceInstruction->getOperand(true), true);
}

void Emulator::bModHandler (long aOp, long bOp)
{
    InstructionPtr targetInstruction = (*core_)[(pc_ + bOp) % coreSize_];
    InstructionPtr sourceInstruction = (*core_)[(pc_ + aOp) % coreSize_];
    targetInstruction->setOperand (sourceInstruction->getOperand(false), false);
}

void Emulator::abModHandler (long aOp, long bOp)
{
    InstructionPtr targetInstruction = (*core_)[(pc_ + bOp) % coreSize_];
    InstructionPtr sourceInstruction = (*core_)[(pc_ + aOp) % coreSize_];
    targetInstruction->setOperand (sourceInstruction->getOperand(true), false);
}

void Emulator::baModHandler (long aOp, long bOp)
{
    InstructionPtr targetInstruction = (*core_)[(pc_ + bOp) % coreSize_];
    InstructionPtr sourceInstruction = (*core_)[(pc_ + aOp) % coreSize_];
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
    (*core_)[(pc_ + bOp) % coreSize_] = (*core_)[(pc_ + aOp) % coreSize_];
}

void Emulator::applyModifier (InstructionPtr instruction)
{
    OperandPtr aArg = instruction->getOperand(true);
    OperandPtr bArg = instruction->getOperand(false);

    Token::TokenType aModifier = std::get<2> (*aArg);
    if (aModifier != Token::end)
        boost::bind (&Emulator::modifierMapping_.at(aModifier), this, std::get<1> (*aArg), std::get<1> (*bArg));
    Token::TokenType bModifier = std::get<2> (*bArg);
    if (bModifier != Token::end)
        boost::bind (&Emulator::modifierMapping_.at(bModifier), this, std::get<1> (*aArg), std::get<1> (*bArg));
}

Emulator::Emulator (unsigned long coreSize, int maxInvoked) : coreSize_(coreSize), nrInvoked_(0), firstCurrent_(true),
                                                              maxInvoked_(maxInvoked), pc_(0)
{
    core_ = std::make_shared<Core> (Core ());
    core_->reserve(coreSize);

    // initialize core with dat 0, 0
    for (int i = 0; i < coreSize; ++i)
    {
        // Token::end marks no modifier/addressing mode
        Operand aOperand = std::make_tuple<> (Token::end, 0, Token::end);
        Operand bOperand = std::make_tuple<> (Token::end, 0, Token::end);
        core_->push_back (std::make_shared<TwoArgsInstruction> (TwoArgsInstruction (Token::dat, aOperand, bOperand)));
    }

    processIdGenerator_ = 0;
    firstWarrior_ = std::make_shared<Warrior> (Warrior ());
    secondWarrior_ = std::make_shared<Warrior> (Warrior ());
    init();
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
        i = outerInst->getInstructions(*core_, i % coreSize_, coreSize_);
    });

    long secondPC = findPCForSecond(firstPC, nrInstrFirst, nrInstrSecond);
    secondWarrior_->createProcess(processIdGenerator_++, secondPC);
    long j = secondPC;
    std::for_each(warrior2Code->begin(), warrior2Code->end(), [this, &j] (InstructionPtr outerInst) {
        j = outerInst->getInstructions(*core_, j, coreSize_);
    });

    pc_ = firstPC;
}

Winner Emulator::invokeInstruction ()
{
    if (nrInvoked_ > maxInvoked_)
        return NONE;
    WarriorPtr current = (firstCurrent_ ? firstWarrior_ : secondWarrior_);
    pc_ = current->getPC();

    InstructionPtr instruction = (*core_)[pc_];
    Token::TokenType type = instruction->getType();
    bool notFailed = boost::bind (&Emulator::functions_.at(type), this, type);
    if (notFailed)
        return firstCurrent_ ? SECOND : FIRST;

    current->switchProcess();
    firstCurrent_ = !firstCurrent_;
    ++nrInvoked_;
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