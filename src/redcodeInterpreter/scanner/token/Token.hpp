//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_TOKEN_HPP
#define REDCODEINTERPRETER_TOKEN_HPP

#include <memory>

class Token
{
public:
    enum TokenType {immidiateMode, directMode, indirectMode, AModifier, BModifier, ABModifier, BAModifier, FModifier, XModifier, IModifier, equ, end, forType, rof, uqe,
        dat, mov, add, sub, mul, div, mod, jmz, jmn, djn, spl, cmp, seq, sne, slt, ldp, stp, jmp, nop, comma, numeric, alpha, dot};

    Token(TokenType type) : type_(type)
    {}

    Token (TokenType type, std::string name) : type_(type), name_(name)
    {}

    const std::string & getName () const
    {
        return name_;
    }

    TokenType getType () const
    {
        return type_;
    }

    bool operator==(const Token & other) const
    {
        return (type_ == other.getType() && name_ == other.getName());
    }

private:
    TokenType type_;
    std::string name_;

};

typedef std::shared_ptr<Token> TokenPtr;

#endif //REDCODEINTERPRETER_TOKEN_HPP
