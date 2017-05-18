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

    virtual ~CompositeInstruction ()
    {}

    virtual void insertInstruction (InstructionPtr instruction)
    {
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
        if (Instruction::getType() == Token::forType)
        {
            if (body_.empty())
                counter_ = value;
            else
                body_.back()->insertNumeric(value);
        }
        else
        {
            if (body_.empty())
            {
                //insert to symbol table manager
            }
            else
                body_.back()->insertNumeric(value);
        }
    }

    virtual void insertModifier (Token::TokenType modifier)
    {
        body_.back()->insertModifier(modifier);
    }

private:
    std::list<InstructionPtr> body_;
    long counter_;
    static const std::list<Token::TokenType> composites_;
};

#endif //REDCODEINTERPRETER_MULTIINSTRUCTION_HPP
