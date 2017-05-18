//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_INSTRUCTION_HPP
#define REDCODEINTERPRETER_INSTRUCTION_HPP

#include <memory>
#include "../../scanner/token/Token.hpp"
#include "../../symbolTableManager/identifier/Identifier.hpp"

class Instruction;
typedef std::shared_ptr<Instruction> InstructionPtr;

class Instruction
{
public:
    Instruction (Token::TokenType type) : type_(type)
    {}

    virtual ~Instruction()
    {}

    virtual void insertInstruction (InstructionPtr instruction) = 0;
    virtual void insertAddrMode (Token::TokenType addrMode) = 0;
    virtual void insertNumeric (long value) = 0;
    virtual void insertModifier (Token::TokenType modifier) = 0;

    inline Token::TokenType getType () const
    {
        return type_;
    }

private:
    Token::TokenType type_;

};

#endif //REDCODEINTERPRETER_INSTRUCTION_HPP
