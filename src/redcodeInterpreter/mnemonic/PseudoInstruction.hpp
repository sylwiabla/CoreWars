//
// Created by Sylwia Blach on 4/26/17.
//

#ifndef REDCODEINTERPRETER_PSEUDOINSTRUCTION_HPP
#define REDCODEINTERPRETER_PSEUDOINSTRUCTION_HPP

#include "Mnemonic.hpp"

class PseudoInstruction : public Mnemonic
{
public:
    PseudoInstruction (RedcodeInterpreter::TokenType type) : Mnemonic(type)
    {}


private:
    std::string name_;
};

typedef std::shared_ptr<PseudoInstruction> PseudoInstrPtr;

#endif //REDCODEINTERPRETER_PSEUDOINSTRUCTION_HPP
