//
// Created by Sylwia Blach on 4/26/17.
//

#ifndef REDCODEINTERPRETER_PSEUDOINSTRUCTION_HPP
#define REDCODEINTERPRETER_PSEUDOINSTRUCTION_HPP

#include "Keyword.hpp"

class PseudoInstruction : public Keyword
{
public:
    PseudoInstruction (std::string name) : name_(name)
    {}

private:
    std::string name_;
};

typedef std::shared_ptr<PseudoInstruction> PseudoInstrPtr;

#endif //REDCODEINTERPRETER_PSEUDOINSTRUCTION_HPP
