//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_MODIFIER_HPP
#define REDCODEINTERPRETER_MODIFIER_HPP

#include "Mnemonic.hpp"

class Modifier : public Mnemonic
{
public:
    Modifier(RedcodeInterpreter::TokenType type) : Mnemonic(type)
    {}

private:
    std::string name_;
};

typedef std::shared_ptr<Modifier> ModifierPtr;

#endif //REDCODEINTERPRETER_MODIFIER_HPP
