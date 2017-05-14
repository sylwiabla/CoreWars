//
// Created by Sylwia Blach on 5/11/17.
//

#ifndef REDCODEINTERPRETER_FUNCTION_HPP
#define REDCODEINTERPRETER_FUNCTION_HPP

#include "Identifier.hpp"
#include "../../parser/instruction/CompositeInstruction.hpp"

class Function : public Identifier
{
public:
    Function (std::string name, MultiInstPtr body) :  Identifier(name), body_(body)
    {}

private:
    MultiInstPtr body_;
};

#endif //REDCODEINTERPRETER_FUNCTION_HPP
