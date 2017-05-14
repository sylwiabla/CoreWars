//
// Created by Sylwia Blach on 4/26/17.
//

#ifndef REDCODEINTERPRETER_LABEL_HPP
#define REDCODEINTERPRETER_LABEL_HPP

#include "Identifier.hpp"

class Label : public Identifier
{
public:
    Label (std::string name) : Identifier(RedcodeInterpreter::alpha), name_(name)
    {}

private:
    std::string name_;


};

#endif //REDCODEINTERPRETER_LABEL_HPP
