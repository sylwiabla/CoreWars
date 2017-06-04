//
// Created by Sylwia Blach on 4/26/17.
//

#ifndef REDCODEINTERPRETER_LABEL_HPP
#define REDCODEINTERPRETER_LABEL_HPP

#include "Identifier.hpp"

class Label : public Identifier
{
public:
    Label (std::string name, long value) : Identifier(name, LABEL), value_(value)
    {}

    inline long getValue () const
    {
        return value_;
    }

private:
    long value_;


};

typedef std::shared_ptr<Label> LabelPtr;

#endif //REDCODEINTERPRETER_LABEL_HPP
