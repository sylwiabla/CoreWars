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

class Instruction;
class Emulator;

typedef std::vector<InstructionPtr> Core;
typedef std::shared_ptr<Core> CorePtr;

class Emulator
{
public:
public:
    class Functor
    {
    public:
        Functor ()
        {}
        // returns false - current warrior lost
        virtual bool operator () (Emulator &, InstructionPtr)
        {
            return false;
        }
    };
    typedef std::shared_ptr<Functor> FunctorPtr;

    class MovFunctor : public Functor
    {
    public:
        MovFunctor () : Functor()
        {}

        virtual bool operator () (Emulator &, InstructionPtr);
    };

    class DatFunctor : public Functor
    {
    public:
        DatFunctor () : Functor()
        {}

        virtual bool operator () (Emulator &, InstructionPtr);
    };

    class AddFunctor : public Functor
    {
    public:
        AddFunctor () : Functor()
        {}

        virtual bool operator () (Emulator &, InstructionPtr);
    };

    class SubFunctor : public Functor
    {
    public:
        SubFunctor () : Functor()
        {}

        virtual bool operator () (Emulator &, InstructionPtr);
    };

    class MulFunctor : public Functor
    {
    public:
        MulFunctor () : Functor()
        {}

        virtual bool operator () (Emulator &, InstructionPtr);
    };

    class DivFunctor : public Functor
    {
    public:
        DivFunctor () : Functor()
        {}

        virtual bool operator () (Emulator &, InstructionPtr);
    };

    class ModFunctor : public Functor
    {
    public:
        ModFunctor () : Functor()
        {}

        virtual bool operator () (Emulator &, InstructionPtr);
    };

    class JmzFunctor : public Functor
    {
    public:
        JmzFunctor () : Functor()
        {}

        virtual bool operator () (Emulator &, InstructionPtr);
    };

    class JmnFunctor : public Functor
    {
    public:
        JmnFunctor () : Functor()
        {}

        virtual bool operator () (Emulator &, InstructionPtr);
    };

    class DjnFunctor : public Functor
    {
    public:
        DjnFunctor () : Functor()
        {}

        virtual bool operator () (Emulator &, InstructionPtr);
    };

    class SplFunctor : public Functor
    {
    public:
        SplFunctor () : Functor()
        {}

        virtual bool operator () (Emulator &, InstructionPtr);
    };

    class CmpFunctor : public Functor
    {
    public:
        CmpFunctor () : Functor()
        {}

        virtual bool operator () (Emulator &, InstructionPtr);
    };

    class SeqFunctor : public Functor
    {
    public:
        SeqFunctor () : Functor()
        {}

        virtual bool operator () (Emulator &, InstructionPtr);
    };

    class SneFunctor : public Functor
    {
    public:
        SneFunctor () : Functor()
        {}

        virtual bool operator () (Emulator &, InstructionPtr);
    };

    class SltFunctor : public Functor
    {
    public:
        SltFunctor () : Functor()
        {}

        virtual bool operator () (Emulator &, InstructionPtr);
    };

    class JmpFunctor : public Functor
    {
    public:
        JmpFunctor () : Functor()
        {}

        virtual bool operator () (Emulator &, InstructionPtr);
    };

    class NopFunctor : public Functor
    {
    public:
        NopFunctor () : Functor()
        {}

        virtual bool operator () (Emulator & e, InstructionPtr i)
        {
            return true;
        }
    };

private:
    unsigned long coreSize_;
    Core core_;
    int nrInvoked_;
    int maxInvoked_;
    long pc_;

    WarriorPtr firstWarrior_;
    WarriorPtr secondWarrior_;
    bool firstCurrent_;

    int processIdGenerator_;

    std::unordered_map<Token::TokenType, FunctorPtr, std::EnumClassHash> functors_;

public:
    Emulator (unsigned long coreSize, int maxInvoked, InstructionPtr initInstruction);

    enum Winner {FIRST, SECOND, NONE, WAITING};

    void loadWarriors (CodePtr warrior1Code, CodePtr warrior2Code);
    // returned false - current warrior lost
    Winner invokeInstruction ();

    Core getCore () const
    {
        return core_;
    }

    bool isFirstCurrent () const
    {
        return firstCurrent_;
    }

private:
    long findPCForSecond (long firstBegin, long nrInstrFirst, long nrInstrSecond);

    std::shared_ptr<MovFunctor> movFunctor;
    std::shared_ptr<DatFunctor> datFunctor;
    std::shared_ptr<AddFunctor> addFunctor;
    std::shared_ptr<SubFunctor> subFunctor;
    std::shared_ptr<MulFunctor> mulFunctor;
    std::shared_ptr<DivFunctor> divFunctor;
    std::shared_ptr<ModFunctor> modFunctor;
    std::shared_ptr<JmzFunctor> jmzFunctor;
    std::shared_ptr<JmnFunctor> jmnFunctor;
    std::shared_ptr<DjnFunctor> djnFunctor;
    std::shared_ptr<SplFunctor> splFunctor;
    std::shared_ptr<CmpFunctor> cmpFunctor;
    std::shared_ptr<SeqFunctor> seqFunctor;
    std::shared_ptr<SneFunctor> sneFunctor;
    std::shared_ptr<SltFunctor> sltFunctor;
    std::shared_ptr<JmpFunctor> jmpFunctor;
    std::shared_ptr<NopFunctor> nopFunctor;

public:
    long immediateGetter (long value, long pc);
    long directGetter (long value, long pc);
    long indirectGetter (long value, long pc);

    long getAddress (OperandPtr operand, Token::TokenType addrMode);

    void aModHandler (long, long);
    void bModHandler (long, long);
    void abModHandler (long, long);
    void baModHandler (long, long);
    void fModHandler (long, long);
    void xModHandler (long, long);
    void iModHandler (long, long);

    std::pair <long, long> getAddresses (InstructionPtr instruction);
    void applyModifiers (InstructionPtr instruction);
    void applyModifier (OperandPtr operandA, OperandPtr operandB, Token::TokenType type);

    void setMemoryCell (InstructionPtr newValue, long address)
    {
        core_[address] = newValue;
    }

    // aOperand - target operand
    void setMemoryCell (long newValue, long address, bool aOperand)
    {
        OperandPtr operand = core_[address]->getOperand(aOperand);
        std::get<1> (*operand) = newValue;
    }

    InstructionPtr getMemoryCell (long address)
    {
        return core_[address];
    }

    bool killProcess ()
    {
        WarriorPtr current = firstCurrent_ ? firstWarrior_ : secondWarrior_;
        return current->killProcess_();
    }

    long getCoreSize () const
    {
        return coreSize_;
    }

    void jump (long newAddr)
    {
        WarriorPtr current = firstCurrent_ ? firstWarrior_ : secondWarrior_;
        current->jump(newAddr);
    }

    long getPc () const
    {
        return pc_;
    }

    void createProcess (long address)
    {
        WarriorPtr current = firstCurrent_ ? firstWarrior_ : secondWarrior_;
        current->createProcess(processIdGenerator_++, address);
    }
};

#endif //REDCODEINTERPRETER_EMULATOR_HPP
