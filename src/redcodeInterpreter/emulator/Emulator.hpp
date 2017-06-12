//
// Created by sylwia on 6/7/17.
//

#ifndef REDCODEINTERPRETER_EMULATOR_HPP
#define REDCODEINTERPRETER_EMULATOR_HPP

#include <vector>
#include <list>
#include <atomic>
#include <functional>
#include <memory>
#include <unordered_map>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/function.hpp>
#include "../instruction/Instruction.hpp"
#include "Warrior.hpp"
#include "../parser/Parser.hpp"

class Emulator;

typedef std::vector<InstructionPtr> Core;
typedef std::shared_ptr<Core> CorePtr;
typedef boost::function<bool (InstructionPtr)> RedcodeFunction;
typedef std::unordered_map<Token::TokenType, RedcodeFunction, std::EnumClassHash> RedcodeInstructionsSet;
// second arg - current pc
typedef boost::function<long (Emulator, long, long)> AddressGetter;
typedef std::unordered_map<Token::TokenType, AddressGetter, std::EnumClassHash> AddrModeMapping;
typedef boost::function<void (long, long)> ModifierHandler;
typedef std::unordered_map<Token::TokenType, ModifierHandler, std::EnumClassHash> ModifierMapping;

class Emulator
{
private:
    unsigned long coreSize_;
    CorePtr core_;
    int nrInvoked_;
    int maxInvoked_;
    long pc_;

    WarriorPtr firstWarrior_;
    WarriorPtr secondWarrior_;
    bool firstCurrent_;

    std::atomic_int processIdGenerator_;

    RedcodeInstructionsSet functions_;
    AddrModeMapping addrModesMapping_;
    ModifierMapping modifierMapping_;

public:
    Emulator (unsigned long coreSize, int maxInvoked);

    enum Winner {FIRST, SECOND, NONE};

    void loadWarriors (CodePtr warrior1Code, CodePtr warrior2Code);
    // returned false - current warrior lost
    Winner invokeInstruction ();

    CorePtr getCore () const
    {
        return core_;
    }

    bool isFirstCurrent () const
    {
        return firstCurrent_;
    }

private:
    long findPCForSecond (long firstBegin, long nrInstrFirst, long nrInstrSecond);

    bool movFunction (InstructionPtr);
    bool datFunction (InstructionPtr);
    bool addFunction (InstructionPtr);
    bool subFunction (InstructionPtr);
    bool mulFunction (InstructionPtr);
    bool divFunction (InstructionPtr);
    bool modFunction (InstructionPtr);
    bool jmzFunction (InstructionPtr);
    bool jmnFunction (InstructionPtr);
    bool djnFunction (InstructionPtr);
    bool splFunction (InstructionPtr);
    bool cmpFunction (InstructionPtr);
    bool seqFunction (InstructionPtr);
    bool sneFunction (InstructionPtr);
    bool sltFunction (InstructionPtr);
    bool ldpFunction (InstructionPtr);
    bool stpFunction (InstructionPtr);
    bool jmpFunction (InstructionPtr);
    bool nopFunction (InstructionPtr);

    long immidateGetter (long value, long pc);
    long directGetter (long value, long pc);
    long indirectGetter (long value, long pc);

    void aModHandler (long, long);
    void bModHandler (long, long);
    void abModHandler (long, long);
    void baModHandler (long, long);
    void fModHandler (long, long);
    void xModHandler (long, long);
    void iModHandler (long, long);

    std::pair <long, long> getAddresses (InstructionPtr instruction);
    void applyModifier (InstructionPtr instruction);

    void init ();

};

#endif //REDCODEINTERPRETER_EMULATOR_HPP
