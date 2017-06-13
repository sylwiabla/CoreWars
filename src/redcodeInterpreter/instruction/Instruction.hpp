//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_INSTRUCTION_HPP
#define REDCODEINTERPRETER_INSTRUCTION_HPP

#include <memory>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "../scanner/token/Token.hpp"
#include "../symbolTableManager/identifier/Identifier.hpp"

class Instruction;
typedef std::shared_ptr<Instruction> InstructionPtr;
// stores tuple - addressing mode, operand value, modifier
typedef std::tuple<Token::TokenType, long, Token::TokenType> Operand;
typedef std::shared_ptr<Operand> OperandPtr;

class Instruction
{
public:
    Instruction (Token::TokenType type) : type_(type)
    {}

    virtual ~Instruction()
    {}

    virtual void insertInstruction (const InstructionPtr & instruction, const InstructionPtr & nestedInstruction) = 0;
    virtual void insertAddrMode (Token::TokenType addrMode) = 0;
    virtual void insertNumeric (long value) = 0;
    virtual void insertModifier (Token::TokenType modifier) = 0;
    // returns address right after the last inserted instruction, second arg - start address, third arg - core size
    virtual long getInstructions (std::vector<InstructionPtr> &, long, long) = 0;
    virtual long getNrInstructions () = 0;
    virtual bool needsNumeric () = 0;
    virtual OperandPtr getOperand (bool aOperand) = 0;
    virtual void setOperand (OperandPtr value, bool aOperand) = 0;

    inline Token::TokenType getType () const
    {
        return type_;
    }

private:
    Token::TokenType type_;

};

#endif //REDCODEINTERPRETER_INSTRUCTION_HPP
