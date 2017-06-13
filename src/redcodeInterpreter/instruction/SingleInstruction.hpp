//
// Created by Sylwia Blach on 5/12/17.
//

#ifndef REDCODEINTERPRETER_SINGLEINSTRUCTION_HPP
#define REDCODEINTERPRETER_SINGLEINSTRUCTION_HPP

#include "Instruction.hpp"

class TwoArgsInstruction;
class OneArgsInstruction;
class ZeroArgsInstruction;

typedef std::shared_ptr<TwoArgsInstruction> TwoArgsInstrPtr;
typedef std::shared_ptr<OneArgsInstruction> OneArgsInstrPtr;
typedef std::shared_ptr<ZeroArgsInstruction> ZeroArgsInstrPtr;

class ZeroArgsInstruction : public Instruction
{
public:
    ZeroArgsInstruction (Token::TokenType type) : Instruction(type)
    {}

    virtual void insertAddrMode (Token::TokenType addrMode) {}
    virtual void insertNumeric (long value) {}
    virtual void insertModifier (Token::TokenType modifier) {}
    virtual void insertInstruction (const InstructionPtr & instruction, const InstructionPtr & nestedInstruction) {}

    virtual long getInstructions (std::vector<InstructionPtr> & result, long start, long size)
    {
        result.at((unsigned long) start) = std::make_shared<ZeroArgsInstruction>(*this);
        return (++start) % size;
    }

    virtual long getNrInstructions ()
    {
        return 1;
    }

    virtual bool needsNumeric ()
    {
        return false;
    }

    virtual OperandPtr getOperand (bool aOperand)
    {
        return nullptr;
    }

    virtual void setOperand (OperandPtr value, bool aOperand)
    {}

};

class OneArgsInstruction : public Instruction
{
private:
    OperandPtr aArg;
    bool canModifiers_;
    bool operandInitialized_;

public:
    OneArgsInstruction (Token::TokenType type) : Instruction(type), canModifiers_(true), operandInitialized_(false)
    {}

    OneArgsInstruction (Token::TokenType type, bool canModifiers) : Instruction(type), canModifiers_(canModifiers), operandInitialized_(false)
    {}

    virtual void insertAddrMode (Token::TokenType addrMode)
    {
        std::get<0> (*aArg) = addrMode;
    }

    virtual void insertNumeric (long value)
    {
        std::get<1> (*aArg) = value;
        operandInitialized_ = true;
    }

    virtual void insertModifier (Token::TokenType modifier)
    {
        std::get<2> (*aArg) = modifier;
    }

    virtual void insertInstruction (const InstructionPtr & instruction, const InstructionPtr & nestedInstruction) {};

    virtual long getInstructions (std::vector<InstructionPtr> & result, long start, long size)
    {
        result.at((unsigned long) start) = std::make_shared<OneArgsInstruction> (*this);
        return (++start) % size;
    }

    virtual long getNrInstructions ()
    {
        return 1;
    }

    virtual bool needsNumeric ()
    {
        return !operandInitialized_;
    }

    virtual OperandPtr getOperand (bool aOperand)
    {
        return aArg;
    }

    virtual void setOperand (OperandPtr value, bool aOperand)
    {
        aArg = value;
    }

};

class TwoArgsInstruction : public Instruction
{
public:
    enum InitializationProgress {NO, ONE, BOTH};

private:
    OperandPtr aArg;
    OperandPtr bArg;

    bool canModifiers_;
    InitializationProgress operandsInitialized_;
    InitializationProgress modifiersInitialized_;
    InitializationProgress addrModesInitialized_;

public:
    TwoArgsInstruction (Token::TokenType type) : Instruction(type), canModifiers_(true), operandsInitialized_(NO),
                                                 modifiersInitialized_(NO), addrModesInitialized_(NO)
    {}

    TwoArgsInstruction (Token::TokenType type, bool canModifiers) : Instruction(type), canModifiers_(canModifiers), operandsInitialized_(NO),
                                                                    modifiersInitialized_(NO), addrModesInitialized_(NO)
    {}

    TwoArgsInstruction (Token::TokenType type, const Operand & aOperand, const Operand & bOperand) : Instruction(type), canModifiers_(true)
    {
        *aArg = aOperand;
        *bArg = bOperand;
        operandsInitialized_ = BOTH;
        modifiersInitialized_ = BOTH;
        addrModesInitialized_ = BOTH;
    }

    virtual void insertAddrMode (Token::TokenType addrMode)
    {
        if (addrModesInitialized_ == NO)
        {
            std::get<0> (*aArg) = addrMode;
            addrModesInitialized_ = ONE;
        }
        else
        {
            std::get<0> (*bArg) = addrMode;
            addrModesInitialized_ = BOTH;
        }
    }

    virtual void insertNumeric (long value)
    {
        if (operandsInitialized_ == NO)
        {
            std::get<1> (*aArg) = value;
            operandsInitialized_ = ONE;
        }
        else
        {
            std::get<1> (*bArg) = value;
            operandsInitialized_ = BOTH;
        }
    }

    virtual void insertModifier (Token::TokenType modifier)
    {
        if (modifiersInitialized_ == NO)
        {
            std::get<2> (*aArg) = modifier;
            modifiersInitialized_ = ONE;
        }
        else
        {
            std::get<2> (*bArg) = modifier;
            modifiersInitialized_ = BOTH;
        }
    }

    virtual void insertInstruction (const InstructionPtr & instruction, const InstructionPtr & nestedInstruction) {};

    virtual long getInstructions (std::vector<InstructionPtr> & result, long start, long size)
    {
        result.at((unsigned long) start) = std::make_shared<TwoArgsInstruction>(*this);
        return (++start) % size;
    }

    virtual long getNrInstructions ()
    {
        return 1;
    }

    virtual bool needsNumeric ()
    {
        return (operandsInitialized_ != BOTH);
    }

    virtual OperandPtr getOperand (bool aOperand)
    {
        return aOperand ? aArg : bArg;
    }

    virtual void setOperand (OperandPtr value, bool aOperand)
    {
        (aOperand ? aArg : bArg) = value;
    }

};

#endif //REDCODEINTERPRETER_SINGLEINSTRUCTION_HPP
