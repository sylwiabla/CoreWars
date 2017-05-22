//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_IDENTIFIER_HPP
#define REDCODEINTERPRETER_IDENTIFIER_HPP

#include <memory>

enum IdentifierType {LABEL, FUNCTION};

class Identifier
{
public:
    Identifier (std::string name, IdentifierType type) : name_(name), type_(type)
    {}

    IdentifierType getType () const
    {
        return type_;
    }

private:
    std::string name_;
    IdentifierType type_;

};

typedef std::shared_ptr<Identifier> IdentifierPtr;

#endif //REDCODEINTERPRETER_IDENTIFIER_HPP
