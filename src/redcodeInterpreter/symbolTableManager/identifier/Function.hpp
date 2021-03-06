//
// Created by Sylwia Blach on 5/11/17.
//

#ifndef REDCODEINTERPRETER_FUNCTION_HPP
#define REDCODEINTERPRETER_FUNCTION_HPP

#include "Identifier.hpp"
#include "../../instruction/CompositeInstruction.hpp"

class Function : public Identifier
{
public:
    Function (std::string name, CompInstPtr body) :  Identifier(name, FUNCTION), body_(body)
    {}

    const CompInstPtr & getInstruction () const
    {
        return body_;
    }

private:
    CompInstPtr body_;
};

typedef std::shared_ptr<Function> FunctionPtr;

#endif //REDCODEINTERPRETER_FUNCTION_HPP
