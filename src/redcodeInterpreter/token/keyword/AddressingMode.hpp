//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_ADDRESSINGMODE_HPP
#define REDCODEINTERPRETER_ADDRESSINGMODE_HPP

#include "Keyword.hpp"

class AddressingMode : public Keyword
{
public:
    AddressingMode (char name) : name_(name)
    {}

private:
    char name_;
};

typedef std::shared_ptr<AddressingMode> AddrModePtr;

#endif //REDCODEINTERPRETER_ADDRESSINGMODE_HPP
