//
// Created by Sylwia Blach on 4/26/17.
//

#ifndef REDCODEINTERPRETER_LABEL_HPP
#define REDCODEINTERPRETER_LABEL_HPP

#include "Identifier.hpp"

class Label : public Identifier
{
public:
    Label (std::string name, long value) : Identifier(name), value_(value)
    {}

private:
    std::string name_;
    long value_;


};

#endif //REDCODEINTERPRETER_LABEL_HPP
