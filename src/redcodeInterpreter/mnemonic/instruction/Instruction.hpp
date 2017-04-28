//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_INSTRUCTION_HPP
#define REDCODEINTERPRETER_INSTRUCTION_HPP

#include "../Keyword.hpp"

class Instruction : public Keyword
{
public:
    Instruction ()
    {}

    Instruction (std::string name) : name_(name)
    {}

    void greet ()
    {
        std::cout << "Instruction: " << name_ << std::endl;
    }

private:
    std::string name_;
};

typedef std::shared_ptr<Instruction> InstructionPtr;

#endif //REDCODEINTERPRETER_INSTRUCTION_HPP
