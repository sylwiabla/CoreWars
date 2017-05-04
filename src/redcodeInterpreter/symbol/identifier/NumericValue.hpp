//
// Created by Sylwia Blach on 4/26/17.
//

#ifndef REDCODEINTERPRETER_NUMERICVALUE_HPP
#define REDCODEINTERPRETER_NUMERICVALUE_HPP

#include "Identifier.hpp"

class NumericValue : public Identifier
{
public:
    NumericValue (long value) : Identifier(RedcodeInterpreter::numeric), value_(value)
    {}

private:
    long value_;
};

#endif //REDCODEINTERPRETER_NUMERICVALUE_HPP
