//
// Created by Sylwia Blach on 4/26/17.
//

#ifndef REDCODEINTERPRETER_PSEUDOINSTRUCTION_HPP
#define REDCODEINTERPRETER_PSEUDOINSTRUCTION_HPP

#include "Symbol.hpp"

class PseudoInstruction : public Symbol
{
public:
    PseudoInstruction (RedcodeInterpreter::TokenType type) : Symbol(type)
    {}


private:
    std::string name_;
};

typedef std::shared_ptr<PseudoInstruction> PseudoInstrPtr;

#endif //REDCODEINTERPRETER_PSEUDOINSTRUCTION_HPP
