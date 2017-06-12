//
// Created by Sylwia Blach on 5/18/17.
//

#include "CompositeInstruction.hpp"

const std::list<Token::TokenType> CompositeInstruction::composites_ = {Token::forType, Token::equ};

void CompositeInstruction::insertInstruction (const InstructionPtr & instruction, const InstructionPtr & nestedInstruction)
{
    if (body_.empty())
    {
        body_.push_back(instruction);
        return;
    }
    InstructionPtr last;
    last = body_.back();
    auto iter = std::find(composites_.begin(), composites_.end(), last->getType());
    if ((iter != composites_.end()) && (last == nestedInstruction))
        last->insertInstruction(instruction, nestedInstruction);
    else
        body_.push_back(instruction);
}

void CompositeInstruction::insertNumeric (long value)
{
    if (body_.empty())
        setCounter(value);
    else
        body_.back()->insertNumeric(value);
}

long CompositeInstruction::getInstructions (std::vector<InstructionPtr> & result, long start, long size)
{
    long tempStart = start;
    for (long i = counter_; i > 0; --i)
    {
        for (InstructionPtr instruction : body_)
            tempStart = instruction->getInstructions(result, tempStart, size);
    }
    return (tempStart % size);
}

long CompositeInstruction::getNrInstructions ()
{
    long result = 0;

    for (long i = counter_; i > 0; --i)
    {
        std::for_each (body_.begin(), body_.end(),
                       [&result] (InstructionPtr instruction) {
                           result += instruction->getNrInstructions();}
        );
    }

    return result;
}

long CompositeInstruction::getCounter () const
{
    return counter_;
}
