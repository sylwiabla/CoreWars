//
// Created by Sylwia Blach on 5/12/17.
//

#ifndef REDCODEINTERPRETER_SINGLEINSTRUCTION_HPP
#define REDCODEINTERPRETER_SINGLEINSTRUCTION_HPP

#include "Instruction.hpp"

typedef std::tuple<Token::TokenType, long, Token::TokenType> Operand;

class ZeroArgsInstruction : public Instruction
{
public:
    ZeroArgsInstruction (Token::TokenType type) : Instruction(type)
    {}

    virtual void insertAddrMode (Token::TokenType addrMode) {}
    virtual void insertNumeric (long value) {}
    virtual void insertModifier (Token::TokenType modifier) {}
    virtual void insertInstruction (const InstructionPtr & instruction) {}

};

class OneArgsInstruction : public Instruction
{
public:
    OneArgsInstruction (Token::TokenType type) : Instruction(type), canModifiers_(true)
    {}

    OneArgsInstruction (Token::TokenType type, bool canModifiers) : Instruction(type), canModifiers_(canModifiers)
    {}

    virtual void insertAddrMode (Token::TokenType addrMode)
    {
        std::get<0> (aArg) = addrMode;
    }

    virtual void insertNumeric (long value)
    {
        std::get<1> (aArg) = value;
    }

    virtual void insertModifier (Token::TokenType modifier)
    {
        std::get<2> (aArg) = modifier;
    }

    virtual void insertInstruction (const InstructionPtr & instruction) {};

private:
    Operand aArg;
    bool canModifiers_;

};

class TwoArgsInstruction : public Instruction
{
public:
    TwoArgsInstruction (Token::TokenType type) : Instruction(type), canModifiers_(true)
    {}

    TwoArgsInstruction (Token::TokenType type, bool canModifiers) : Instruction(type), canModifiers_(canModifiers)
    {}

    virtual void insertAddrMode (Token::TokenType addrMode)
    {
        if (std::get<0> (aArg))
            std::get<0> (bArg) = addrMode;
        else
            std::get<0> (aArg) = addrMode;
    }

    virtual void insertNumeric (long value)
    {
        if (std::get<1> (aArg))
            std::get<1> (bArg) = value;
        else
            std::get<1> (aArg) = value;
    }

    virtual void insertModifier (Token::TokenType modifier)
    {
        if (std::get<2> (aArg))
            std::get<2> (bArg) = modifier;
        else
            std::get<2> (aArg) = modifier;
    }

    virtual void insertInstruction (const InstructionPtr & instruction) {};

private:
    Operand aArg;
    Operand bArg;

    bool canModifiers_;
};

typedef std::shared_ptr<TwoArgsInstruction> TwoArgsInstrPtr;
typedef std::shared_ptr<OneArgsInstruction> OneArgsInstrPtr;
typedef std::shared_ptr<ZeroArgsInstruction> ZeroArgsInstrPtr;

#endif //REDCODEINTERPRETER_SINGLEINSTRUCTION_HPP
