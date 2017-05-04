//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_KEYWORD_HPP
#define REDCODEINTERPRETER_KEYWORD_HPP

#include <memory>
#include "../RedcodeInterpreter.hpp"

class Symbol
{
public:
    Symbol(RedcodeInterpreter::TokenType type) : type_(type)
    {}

private:
    RedcodeInterpreter::TokenType type_;

};

typedef std::shared_ptr<Symbol> MnemonicPtr;

#endif //REDCODEINTERPRETER_KEYWORD_HPP
