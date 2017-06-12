//
// Created by Sylwia Blach on 5/12/17.
//

#ifndef REDCODEINTERPRETER_MULTIINSTRUCTION_HPP
#define REDCODEINTERPRETER_MULTIINSTRUCTION_HPP

#include <list>
#include <algorithm>
#include "Instruction.hpp"

class CompositeInstruction;
typedef std::shared_ptr<CompositeInstruction> CompInstPtr;

class CompositeInstruction : public Instruction
{
public:
    CompositeInstruction (Token::TokenType type) : Instruction(type), counter_(1)
    {}

    CompositeInstruction (Token::TokenType type, long counter) : Instruction(type), counter_(counter)
    {}

    ~CompositeInstruction ()
    {}

    void insertInstruction (const InstructionPtr & instruction, const InstructionPtr & nestedInstruction);

    void insertAddrMode (Token::TokenType addrMode)
    {
        body_.back()->insertAddrMode(addrMode);
    }

    void insertNumeric (long value);

    void insertModifier (Token::TokenType modifier)
    {
        body_.back()->insertModifier(modifier);
    }

    const std::list<InstructionPtr> & getBody () const
    {
        return body_;
    }

    long getInstructions (std::vector<InstructionPtr> & result, long start, long size);
    long getNrInstructions ();

    long getCounter () const;

    void setCounter (long counter)
    {
        counter_ = counter;
    }

    bool needsNumeric ()
    {
        if (body_.empty())
        {
            if (getType() == Token::forType)
                return true;
        }
        else
            return body_.back()->needsNumeric();
    }

    void setOperand (OperandPtr value, bool aOperand)
    {}

    OperandPtr getOperand (bool aOperand)
    {
        return nullptr;
    }

private:
    long counter_;
    static const std::list<Token::TokenType> composites_;
    std::list<InstructionPtr> body_;
};

#endif //REDCODEINTERPRETER_MULTIINSTRUCTION_HPP
