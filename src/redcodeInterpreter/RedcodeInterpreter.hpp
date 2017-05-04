//
// Created by Sylwia Blach on 4/26/17.
//

#ifndef REDCODEINTERPRETER_REDCODEINTERPRETER_HPP
#define REDCODEINTERPRETER_REDCODEINTERPRETER_HPP

#include <iostream>
#include <unordered_map>

class RedcodeInterpreter
{
public:
    static RedcodeInterpreter & getInstance()
    {
        static RedcodeInterpreter instance;
        return instance;
    }

    enum TokenType {immidiateMode, directMode, indirectMode, AModifier, BModifier, ABModifier, BAModifier, FModifier, XModifier, IModifier, equ, org, end, forType, rof, pin,
        dat, mov, add, sub, mul, div, mod, jmz, jmn, djn, spl, cmp, seq, sne, slt, ldp, stp, jmp, nop, comma, numeric, alpha};

    static const std::unordered_map<std::string, TokenType> keywords_;
    static const char COMMENT_START = ';';
    typedef std::unordered_map<std::string, RedcodeInterpreter::TokenType>::const_iterator TokenIter;

private:
    RedcodeInterpreter ()
    {}

    RedcodeInterpreter (RedcodeInterpreter const&) = delete;
    void operator=(RedcodeInterpreter const&) = delete;
};

#endif //REDCODEINTERPRETER_REDCODEINTERPRETER_HPP
