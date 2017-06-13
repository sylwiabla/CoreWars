//
// Created by Sylwia Blach on 4/18/17.
//

/*
                    Redcode Grammar
STATS -> STAT STATS
STATS -> ''
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
EQUV -> num uqe
EQUV -> lab uqe
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
#include <boost/lexical_cast.hpp>
#include "../errorLogger/ErrorLogger.hpp"
#include "../scanner/Scanner.hpp"
#include "../instruction/SingleInstruction.hpp"
#include "../instruction/CompositeInstruction.hpp"
#include "../symbolTableManager/SymbolTableManager.hpp"
#include "../symbolTableManager/identifier/Label.hpp"

typedef std::list<InstructionPtr> Code;
typedef std::shared_ptr<Code> CodePtr;

class Parser;
typedef std::shared_ptr<Parser> ParserPtr;
namespace std
{
    struct EnumClassHash;
}

class Parser
{
public:
    Parser(ErrorLoggerPtr logger, ScannerPtr scanner, SymbolTablePtr symbolTableManager) : logger_(logger), scanner_(std::move(scanner)),
                                                                                           symbolTableManager_(symbolTableManager)
    {
        stack_.push(std::make_shared<Symbol> (true, end));      // push end symbol
        stack_.push(std::make_shared<Symbol> (false, STATS));  // push start symbol - STATS
    }

    CodePtr parse ();

    enum SymbolType {STATS, STAT, INST, EQU, FOR, label, inst0, inst1, inst2, OP, comma, addMode, OP1, OP_NAME, numeric, MOD, equ,
        EQU_VAL, STS, uqe, forType, rof, dot, mod, epsilon, end};

private:
    class ProductionRule;

public:
    class Symbol;

    typedef std::shared_ptr<Symbol> SymbolPtr;
    typedef std::shared_ptr<ProductionRule> ProductionPtr;
    typedef const std::unordered_map<std::pair<Symbol, Symbol>, ProductionPtr> PredictTable;
    typedef const std::unordered_map<Token::TokenType, SymbolType, std::EnumClassHash> Terminals;
    typedef std::vector<Parser::SymbolPtr> Derivation;

    class Symbol
    {
    private:
        bool isTerminal_;
        Parser::SymbolType type_;

    public:
        Symbol () : isTerminal_(true), type_(end)
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

private:
    ErrorLoggerPtr logger_;
    ScannerPtr scanner_;
    SymbolTablePtr symbolTableManager_;

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

    static const std::vector<ProductionPtr> productions_;
    static PredictTable predictTable_;
    std::stack<SymbolPtr> stack_;
    std::stack<CompInstPtr> nestedInstructions_;
    std::list<InstructionPtr> code_;
    static Terminals terminals_;

    SymbolPtr mapTokenToSymbol (TokenPtr token);
    void accept (TokenPtr token, SymbolType type);
    void derive(Token::Type type, SymbolPtr input);
    void logError(Token::Type type);

    const InstructionPtr acceptInst (Token::TokenType tokenType, SymbolType symbolType);
    void acceptAddrMode (Token::Type type);
    void acceptNumeric (std::string value);
    void acceptModifier (Token::Type type);

    void acceptComposite (Token::Type type);
    void acceptLabel (std::string name);
    void acceptUqe ();
    void acceptRof ();
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

    template <> struct hash<std::pair<Parser::Symbol, Parser::Symbol>>
    {
        std::size_t operator()(const std::pair<Parser::Symbol, Parser::Symbol> & key) const
        {
            using std::size_t;

            Parser::SymbolType firstType = key.first.getType();
            Parser::SymbolType secondType = key.second.getType();
            return (static_cast<std::size_t>(firstType) << 1) ^ (static_cast<std::size_t>(secondType) << 1) >> 1;
        }
    };
}

#endif //REDCODEINTERPRETER_PARSER_HPP
