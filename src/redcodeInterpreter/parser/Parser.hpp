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
#include <unordered_map>
#include <stack>
#include "../errorLogger/ErrorLogger.hpp"
#include "../scanner/Scanner.hpp"
#include "instruction/SingleInstruction.hpp"
#include "instruction/CompositeInstruction.hpp"

class Parser;
typedef std::shared_ptr<Parser> ParserPtr;
namespace std
{
    struct EnumClassHash;
}

class Parser
{
public:
    Parser(ErrorLoggerPtr logger, ScannerPtr scanner) : logger_(logger), scanner_(std::move(scanner))
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
    typedef const std::unordered_map<Token::TokenType, SymbolType, std::EnumClassHash> Terminals;
    typedef const std::unordered_map<std::pair<SymbolPtr, SymbolPtr>, ProductionPtr> PredictTable;

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

        const std::vector<SymbolPtr> & getDerivation () const
        {
            return derivation_;
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

    static Terminals terminals_;
    static const std::vector<SymbolPtr> symbols_;
    static const std::vector<ProductionPtr> productions_;
    static PredictTable predictTable_;
    std::stack<SymbolPtr> stack_;
    std::stack<CompInstPtr> nestedInstructions_;
    std::list<InstructionPtr> code_;

    SymbolPtr mapTokenToSymbol (TokenPtr token);
    void accept (TokenPtr token, SymbolType type);
    void derive(SymbolPtr input);
    void logError();

    const InstructionPtr & acceptInst (Token::TokenType tokenType, SymbolType symbolType);
    void acceptAddrMode (Token::TokenType type);
    void acceptNumeric (std::string value);
    void acceptModifier (Token::TokenType type);
    void acceptFor (Token::TokenType type);
};

namespace std
{
    struct EnumClassHash
    {
        template<typename T>
        std::size_t operator()(T t) const
        {
            return static_cast<std::size_t>(t);
        }
    };

    template <> struct hash<std::pair<Parser::SymbolPtr, Parser::SymbolPtr>>
    {
        std::size_t operator()(const std::pair<Parser::SymbolPtr, Parser::SymbolPtr> & key) const
        {
            using std::size_t;

            Parser::SymbolType firstType = key.first->getType();
            Parser::SymbolType secondType = key.second->getType();
            return (static_cast<std::size_t>(firstType) << 1) ^ (static_cast<std::size_t>(secondType) << 1) >> 1;
        }
    };
}

#endif //REDCODEINTERPRETER_PARSER_HPP
