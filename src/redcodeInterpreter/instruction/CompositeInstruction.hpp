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

    virtual ~CompositeInstruction ()
    {}

    virtual void insertInstruction (const InstructionPtr & instruction)
    {
        if (body_.empty())
            body_.push_back(instruction);
        InstructionPtr last;
        last = body_.back();
        auto iter = std::find(composites_.begin(), composites_.end(), last->getType());
        if (iter != composites_.end())
            last->insertInstruction(instruction);
        else
            body_.push_back(instruction);
    }

    virtual void insertAddrMode (Token::TokenType addrMode)
    {
        body_.back()->insertAddrMode(addrMode);
    }

    virtual void insertNumeric (long value)
    {
        if (body_.empty())
            setCounter(value);
        else
            body_.back()->insertNumeric(value);
    }

    virtual void insertModifier (Token::TokenType modifier)
    {
        body_.back()->insertModifier(modifier);
    }

    const std::list<InstructionPtr> & getBody () const
    {
        return body_;
    }

    virtual void getInstructions (std::vector<InstructionPtr> & result)
    {
        for (int i = counter_; i > 0; --i)
        {
            for (InstructionPtr instruction : body_)
                instruction->getInstructions(result);
        }
    }

    long getCounter () const
    {
        return counter_;
    }

    void setCounter (long counter)
    {
        counter_ = counter;
    }

private:
    std::list<InstructionPtr> body_;
    long counter_;
    static const std::list<Token::TokenType> composites_;
};

#endif //REDCODEINTERPRETER_MULTIINSTRUCTION_HPP
