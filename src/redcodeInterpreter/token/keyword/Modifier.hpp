//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_MODIFIER_HPP
#define REDCODEINTERPRETER_MODIFIER_HPP

#include "Keyword.hpp"

class Modifier : public Keyword
{
public:
    Modifier()
    {}
};

typedef std::shared_ptr<Modifier> ModifierPtr;

#endif //REDCODEINTERPRETER_MODIFIER_HPP
