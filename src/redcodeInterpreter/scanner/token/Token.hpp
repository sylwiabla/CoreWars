//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_TOKEN_HPP
#define REDCODEINTERPRETER_TOKEN_HPP

#include <memory>
#include <unordered_map>

class Token
{
public:
    enum TokenType {immediateMode, directMode, indirectMode, AModifier, BModifier, ABModifier, BAModifier, FModifier, XModifier, IModifier, equ, end, forType, rof, uqe,
        dat, mov, add, sub, mul, div, mod, jmz, jmn, djn, spl, cmp, seq, sne, slt, jmp, nop, comma, numeric, alpha, dot};

    enum TokenSubType {inst0, inst1, inst2, addMode, modifier, none};

    class Type;

    Token(TokenType tokenType, std::string name) : type_(tokenType, name), value_("")
    {}

    Token(TokenType tokenType, TokenSubType subType, std::string name) : type_(tokenType, subType, name), value_("")
    {}

    Token (TokenType tokenType, std::string name, std::string value) : type_(tokenType, name), value_(value)
    {}

    Token(Type type) : type_(type), value_("")
    {}

    Token(Type type, std::string value) : type_(type), value_(value)
    {}

    const std::string & getValue () const
    {
        return value_;
    }

    Type getType () const
    {
        return type_;
    }

    bool operator==(const Token & other) const
    {
        return (type_ == other.getType() && value_ == other.getValue());
    }

    class Type
    {
        TokenType tokenType_;
        TokenSubType subType_;
        std::string name_;

    public:

        Type () : tokenType_(end), subType_(none), name_("")
        {}

        Type (TokenType tokenType, std::string name) : tokenType_(tokenType), name_(name), subType_(none)
        {}

        Type (TokenType tokenType, TokenSubType subType, std::string name) : tokenType_(tokenType), name_(name), subType_(subType)
        {}

        bool operator==(const Type & other) const
        {
            return (other.subType_ == subType_) && (other.tokenType_ == tokenType_);
        }

        bool operator==(const TokenType & other) const
        {
            return (other == tokenType_);
        }

        TokenType getTokenType() const
        {
            return tokenType_;
        }

        const std::string & getName () const
        {
            return name_;
        }
    };

private:
    Type type_;
    std::string value_;


};

typedef std::shared_ptr<Token> TokenPtr;

#endif //REDCODEINTERPRETER_TOKEN_HPP
