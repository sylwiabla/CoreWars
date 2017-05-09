//
// Created by Sylwia Blach on 4/18/17.
//

/*
                    Redcode Grammar
S -> STAT S
S -> ''
STAT -> INST
STAT -> EQU
STAT -> FOR
STAT -> lab
INST -> inst0
INST -> inst1 OP
INST -> inst2 OP , OP
OP -> add OP1
OP -> OP1
OP1 -> OPN MOD
MOD -> . mod
MOD -> ''
OPN -> num
OPN -> lab
FOR -> for OPN STS rof
EQU -> equ lab EQUV
EQUV -> num
EQUV -> lab
EQUV -> STS uqe
STS -> INST S
STS -> FOR S
*/

#ifndef REDCODEINTERPRETER_PARSER_HPP
#define REDCODEINTERPRETER_PARSER_HPP

#include <memory>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <stack>
#include "../errorLogger/ErrorLogger.hpp"
#include "../scanner/Scanner.hpp"
#include "../RedcodeInterpreter.hpp"

/*#include "../symbol/AddressingMode.hpp"
#include "../symbol/Modifier.hpp"
#include "../symbol/PseudoInstruction.hpp"
#include "../symbol/identifier/Label.hpp"
#include "../symbol/identifier/NumericValue.hpp"
#include "../symbol/instruction/OneArgsInstruction.hpp"
#include "../symbol/instruction/TwoArgsInstruction.hpp"
#include "../symbol/instruction/ZeroArgsInstruction.hpp"*/

class Parser;
typedef std::shared_ptr<Parser> ParserPtr;

class Parser
{
public:
    Parser(ErrorLoggerPtr logger, ScannerPtr scanner) : logger_(logger), scanner_(scanner)
    {
        stack_.push(symbols_[25]); // push end symbol
        stack_.push(symbols_[0]);  // push start symbol - STATS
    }

    void parse ();

    enum SymbolType {STATS, STAT, INST, EQU, FOR, label, inst0, inst1, inst2, OP, comma, addMode, OP1, OP_NAME, numeric, MOD, equ, EQU_VAL, STS, uqe, forType, rof, dot, mod, epsilon, end};

private:
    class Symbol;
    class ProductionRule;

public:
    typedef std::shared_ptr<Symbol> SymbolPtr;
    typedef std::shared_ptr<ProductionRule> ProductionPtr;

private:
    ErrorLoggerPtr logger_;
    ScannerPtr scanner_;

    class Symbol
    {
    private:
        bool isTerminal_;
        Parser::SymbolType type_;

    public:
        Symbol ()
        {}

        Symbol (bool isTerminal, Parser::SymbolType type) : isTerminal_(isTerminal), type_(type)
        {}

        inline bool isTerminal () const
        {
            return isTerminal_;
        }

        inline Parser::SymbolType getType () const
        {
            return type_;
        }

        bool operator== (const Symbol & symbol) const
        {
            return (isTerminal_ == symbol.isTerminal()) && (type_ == symbol.getType());
        }
    };

    class ProductionRule
    {
    private:
        SymbolPtr nonterminal_;
        std::vector<SymbolPtr> derivation_;

    public:
        ProductionRule(SymbolPtr nonterminal, const std::vector<SymbolPtr> & derivation)
        {
            nonterminal_ = nonterminal;
            derivation_ = derivation;
        }
    };

    struct EnumClassHash
    {
        template <typename T>
        std::size_t operator()(T t) const
        {
            return static_cast<std::size_t>(t);
        }
    };

    static const std::vector<Parser::SymbolPtr> statsStatRule;
    static const std::vector<Parser::SymbolPtr> statsEpsRule;
    static const std::vector<Parser::SymbolPtr> statInstRule;
    static const std::vector<Parser::SymbolPtr> statEquRule;
    static const std::vector<Parser::SymbolPtr> statForRule;
    static const std::vector<Parser::SymbolPtr> statLabRule;
    static const std::vector<Parser::SymbolPtr> instInst0Rule;
    static const std::vector<Parser::SymbolPtr> instInst1Rule;
    static const std::vector<Parser::SymbolPtr> instInst2Rule;
    static const std::vector<Parser::SymbolPtr> opAddRule;
    static const std::vector<Parser::SymbolPtr> opOp1Rule;
    static const std::vector<Parser::SymbolPtr> op1Rule;
    static const std::vector<Parser::SymbolPtr> opNameNumRule;
    static const std::vector<Parser::SymbolPtr> opNameLabRule;
    static const std::vector<Parser::SymbolPtr> equRule;
    static const std::vector<Parser::SymbolPtr> equVNumRule;
    static const std::vector<Parser::SymbolPtr> equVLabRule;
    static const std::vector<Parser::SymbolPtr> equVStsRule;
    static const std::vector<Parser::SymbolPtr> stsInstRule;
    static const std::vector<Parser::SymbolPtr> stsForRule;
    static const std::vector<Parser::SymbolPtr> forRule;
    static const std::vector<Parser::SymbolPtr> modDotRule;
    static const std::vector<Parser::SymbolPtr> modEpsRule;

    static const std::unordered_map<RedcodeInterpreter::TokenType, SymbolType, EnumClassHash> terminals_;
    static const std::vector<SymbolPtr> symbols_;
    static const std::vector<ProductionPtr> productions_;
    static const std::map<std::tuple<SymbolPtr, SymbolPtr>, ProductionPtr> predictTable_;
    std::stack<SymbolPtr> stack_;

    SymbolPtr mapTokenToSymbol (TokenPtr token);
    void accept ();
    void derive();
    void logError();
};

#endif //REDCODEINTERPRETER_PARSER_HPP
