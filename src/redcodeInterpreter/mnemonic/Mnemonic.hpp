//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_KEYWORD_HPP
#define REDCODEINTERPRETER_KEYWORD_HPP

#include <memory>
#include "../RedcodeInterpreter.hpp"

class Mnemonic
{
public:
    Mnemonic(RedcodeInterpreter::TokenType type) : type_(type)
    {}

private:
    RedcodeInterpreter::TokenType type_;

};

typedef std::shared_ptr<Mnemonic> MnemonicPtr;

#endif //REDCODEINTERPRETER_KEYWORD_HPP
