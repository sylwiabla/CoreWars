//
// Created by Sylwia Blach on 4/18/17.
//

#include "Parser.hpp"

const std::unordered_map<RedcodeInterpreter::TokenType, Parser::SymbolType, Parser::EnumClassHash> Parser::terminals_ = {{RedcodeInterpreter::immidiateMode, addMode}, {RedcodeInterpreter::directMode, addMode},
                                                                                                                         {RedcodeInterpreter::indirectMode, addMode}, {RedcodeInterpreter::AModifier, mod}, {RedcodeInterpreter::BModifier, mod},
                                                                                                                         {RedcodeInterpreter::ABModifier, mod}, {RedcodeInterpreter::BAModifier, mod}, {RedcodeInterpreter::FModifier, mod},
                                                                                                                         {RedcodeInterpreter::XModifier, mod}, {RedcodeInterpreter::IModifier, mod}, {RedcodeInterpreter::equ, equ},
                                                                                                                         {RedcodeInterpreter::forType, forType}, {RedcodeInterpreter::rof, rof}, {RedcodeInterpreter::dat, inst2},
                                                                                                                         {RedcodeInterpreter::mov, inst2}, {RedcodeInterpreter::add, inst2}, {RedcodeInterpreter::sub, inst2},
                                                                                                                         {RedcodeInterpreter::mul, inst2}, {RedcodeInterpreter::div, inst2}, {RedcodeInterpreter::mod, inst2},
                                                                                                                         {RedcodeInterpreter::jmz, inst2}, {RedcodeInterpreter::jmn, inst2}, {RedcodeInterpreter::djn, inst2},
                                                                                                                         {RedcodeInterpreter::spl, inst2}, {RedcodeInterpreter::cmp, inst2}, {RedcodeInterpreter::seq, inst2},
                                                                                                                         {RedcodeInterpreter::sne, inst2}, {RedcodeInterpreter::slt, inst2}, {RedcodeInterpreter::ldp, inst2},
                                                                                                                         {RedcodeInterpreter::stp, inst2}, {RedcodeInterpreter::jmp, inst1}, {RedcodeInterpreter::nop, inst0},
                                                                                                                         {RedcodeInterpreter::comma, comma}, {RedcodeInterpreter::numeric, numeric}, {RedcodeInterpreter::alpha, label},
                                                                                                                         {RedcodeInterpreter::dot, dot}};

const std::vector<Parser::SymbolPtr> Parser::symbols_ = {std::make_shared<Symbol> (false, STATS), std::make_shared<Symbol> (false, STAT), std::make_shared<Symbol> (true, epsilon),
                                                         std::make_shared<Symbol> (false, INST), std::make_shared<Symbol> (false, EQU), std::make_shared<Symbol> (false, FOR), std::make_shared<Symbol> (true, label),
                                                         std::make_shared<Symbol> (true, inst0), std::make_shared<Symbol> (true, inst1), std::make_shared<Symbol> (false, OP),
                                                         std::make_shared<Symbol> (true, inst2), std::make_shared<Symbol> (true, comma), std::make_shared<Symbol> (true, addMode),
                                                         std::make_shared<Symbol> (false, OP1), std::make_shared<Symbol> (false, OP_NAME), std::make_shared<Symbol> (false, MOD),
                                                         std::make_shared<Symbol> (true, numeric), std::make_shared<Symbol> (true, equ), std::make_shared<Symbol> (false, EQU_VAL),
                                                         std::make_shared<Symbol> (false, STS), std::make_shared<Symbol> (true, uqe), std::make_shared<Symbol> (true, forType),
                                                         std::make_shared<Symbol> (true, rof), std::make_shared<Symbol> (true, dot), std::make_shared<Symbol> (true, mod), std::make_shared<Symbol> (true, end)};

const std::vector<Parser::SymbolPtr> Parser::statsStatRule = {Parser::symbols_[0], Parser::symbols_[1]};
const std::vector<Parser::SymbolPtr> Parser::statsEpsRule = {Parser::symbols_[2]};
const std::vector<Parser::SymbolPtr> Parser::statInstRule = {Parser::symbols_[3]};
const std::vector<Parser::SymbolPtr> Parser::statEquRule = {Parser::symbols_[4]};
const std::vector<Parser::SymbolPtr> Parser::statForRule = {Parser::symbols_[5]};
const std::vector<Parser::SymbolPtr> Parser::statLabRule = {Parser::symbols_[6]};
const std::vector<Parser::SymbolPtr> Parser::instInst0Rule = {Parser::symbols_[7]};
const std::vector<Parser::SymbolPtr> Parser::instInst1Rule = {Parser::symbols_[9], Parser::symbols_[8]};
const std::vector<Parser::SymbolPtr> Parser::instInst2Rule = {Parser::symbols_[9], Parser::symbols_[11], Parser::symbols_[9], Parser::symbols_[10]};
const std::vector<Parser::SymbolPtr> Parser::opAddRule = {Parser::symbols_[13], Parser::symbols_[12]};
const std::vector<Parser::SymbolPtr> Parser::opOp1Rule = {Parser::symbols_[13]};
const std::vector<Parser::SymbolPtr> Parser::op1Rule = {Parser::symbols_[15], Parser::symbols_[14]};
const std::vector<Parser::SymbolPtr> Parser::opNameNumRule = {Parser::symbols_[16]};
const std::vector<Parser::SymbolPtr> Parser::opNameLabRule = {Parser::symbols_[6]};
const std::vector<Parser::SymbolPtr> Parser::equRule = {Parser::symbols_[18], Parser::symbols_[6], Parser::symbols_[17]};
const std::vector<Parser::SymbolPtr> Parser::equVNumRule = {Parser::symbols_[16]};
const std::vector<Parser::SymbolPtr> Parser::equVLabRule = {Parser::symbols_[6]};
const std::vector<Parser::SymbolPtr> Parser::equVStsRule = {Parser::symbols_[20], Parser::symbols_[19]};
const std::vector<Parser::SymbolPtr> Parser::stsInstRule = {Parser::symbols_[0], Parser::symbols_[3]};
const std::vector<Parser::SymbolPtr> Parser::stsForRule = {Parser::symbols_[0], Parser::symbols_[5]};
const std::vector<Parser::SymbolPtr> Parser::forRule = {Parser::symbols_[22], Parser::symbols_[19], Parser::symbols_[14], Parser::symbols_[21]};
const std::vector<Parser::SymbolPtr> Parser::modDotRule = {Parser::symbols_[24], Parser::symbols_[23]};
const std::vector<Parser::SymbolPtr> Parser::modEpsRule = {Parser::symbols_[2]};

const std::vector<Parser::ProductionPtr> Parser::productions_ = {std::make_shared<ProductionRule> (Parser::symbols_[0], Parser::statsStatRule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[0], Parser::statsEpsRule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[1], Parser::statInstRule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[1], Parser::statEquRule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[1], Parser::statForRule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[1], Parser::statLabRule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[3], Parser::instInst0Rule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[3], Parser::instInst1Rule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[3], Parser::instInst2Rule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[9], Parser::opAddRule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[9], Parser::opOp1Rule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[13], Parser::op1Rule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[14], Parser::opNameNumRule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[14], Parser::opNameLabRule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[4], Parser::equRule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[18], Parser::equVNumRule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[18], Parser::equVLabRule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[18], Parser::equVStsRule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[19], Parser::stsInstRule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[19], Parser::stsForRule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[5], Parser::forRule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[15], Parser::modDotRule),
                                                                 std::make_shared<ProductionRule> (Parser::symbols_[15], Parser::modEpsRule)};

// STATS
const std::map<std::tuple<Parser::SymbolPtr, Parser::SymbolPtr>, Parser::ProductionPtr> Parser::predictTable_ = {{std::make_pair(Parser::symbols_[0], Parser::symbols_[6]), Parser::productions_[0]},
                                                                                                                 {std::make_pair(Parser::symbols_[0], Parser::symbols_[7]), Parser::productions_[0]},
                                                                                                                 {std::make_pair(Parser::symbols_[0], Parser::symbols_[8]), Parser::productions_[0]},
                                                                                                                 {std::make_pair(Parser::symbols_[0], Parser::symbols_[10]), Parser::productions_[0]},
                                                                                                                 {std::make_pair(Parser::symbols_[0], Parser::symbols_[21]), Parser::productions_[0]},
                                                                                                                 {std::make_pair(Parser::symbols_[0], Parser::symbols_[22]), Parser::productions_[1]},
                                                                                                                 {std::make_pair(Parser::symbols_[0], Parser::symbols_[17]), Parser::productions_[0]},
                                                                                                                 {std::make_pair(Parser::symbols_[0], Parser::symbols_[20]), Parser::productions_[1]},
                                                                                                                 {std::make_pair(Parser::symbols_[0], Parser::symbols_[25]), Parser::productions_[1]},
        // STAT
                                                                                                                 {std::make_pair(Parser::symbols_[1], Parser::symbols_[6]), Parser::productions_[5]},
                                                                                                                 {std::make_pair(Parser::symbols_[1], Parser::symbols_[7]), Parser::productions_[2]},
                                                                                                                 {std::make_pair(Parser::symbols_[1], Parser::symbols_[8]), Parser::productions_[2]},
                                                                                                                 {std::make_pair(Parser::symbols_[1], Parser::symbols_[10]), Parser::productions_[2]},
                                                                                                                 {std::make_pair(Parser::symbols_[1], Parser::symbols_[21]), Parser::productions_[4]},
                                                                                                                 {std::make_pair(Parser::symbols_[1], Parser::symbols_[17]), Parser::productions_[3]},
        // INST
                                                                                                                 {std::make_pair(Parser::symbols_[3], Parser::symbols_[7]), Parser::productions_[6]},
                                                                                                                 {std::make_pair(Parser::symbols_[3], Parser::symbols_[8]), Parser::productions_[7]},
                                                                                                                 {std::make_pair(Parser::symbols_[3], Parser::symbols_[10]), Parser::productions_[8]},
        // OP
                                                                                                                 {std::make_pair(Parser::symbols_[9], Parser::symbols_[6]), Parser::productions_[10]},
                                                                                                                 {std::make_pair(Parser::symbols_[9], Parser::symbols_[12]), Parser::productions_[9]},
                                                                                                                 {std::make_pair(Parser::symbols_[9], Parser::symbols_[16]), Parser::productions_[10]},
        // OP1
                                                                                                                 {std::make_pair(Parser::symbols_[13], Parser::symbols_[6]), Parser::productions_[11]},
                                                                                                                 {std::make_pair(Parser::symbols_[13], Parser::symbols_[16]), Parser::productions_[11]},
        // MOD
                                                                                                                 {std::make_pair(Parser::symbols_[15], Parser::symbols_[6]), Parser::productions_[22]},
                                                                                                                 {std::make_pair(Parser::symbols_[15], Parser::symbols_[7]), Parser::productions_[22]},
                                                                                                                 {std::make_pair(Parser::symbols_[15], Parser::symbols_[8]), Parser::productions_[22]},
                                                                                                                 {std::make_pair(Parser::symbols_[15], Parser::symbols_[10]), Parser::productions_[22]},
                                                                                                                 {std::make_pair(Parser::symbols_[15], Parser::symbols_[11]), Parser::productions_[22]},
                                                                                                                 {std::make_pair(Parser::symbols_[15], Parser::symbols_[23]), Parser::productions_[21]},
                                                                                                                 {std::make_pair(Parser::symbols_[15], Parser::symbols_[21]), Parser::productions_[22]},
                                                                                                                 {std::make_pair(Parser::symbols_[15], Parser::symbols_[22]), Parser::productions_[22]},
                                                                                                                 {std::make_pair(Parser::symbols_[15], Parser::symbols_[17]), Parser::productions_[22]},
                                                                                                                 {std::make_pair(Parser::symbols_[15], Parser::symbols_[20]), Parser::productions_[22]},
                                                                                                                 {std::make_pair(Parser::symbols_[15], Parser::symbols_[25]), Parser::productions_[22]},
        // OP_NAME
                                                                                                                 {std::make_pair(Parser::symbols_[14], Parser::symbols_[6]), Parser::productions_[13]},
                                                                                                                 {std::make_pair(Parser::symbols_[14], Parser::symbols_[16]), Parser::productions_[12]},
        // FOR
                                                                                                                 {std::make_pair(Parser::symbols_[5], Parser::symbols_[21]), Parser::productions_[20]},
        // EQU
                                                                                                                 {std::make_pair(Parser::symbols_[4], Parser::symbols_[17]), Parser::productions_[14]},
        // EQU_VAL
                                                                                                                 {std::make_pair(Parser::symbols_[18], Parser::symbols_[6]), Parser::productions_[16]},
                                                                                                                 {std::make_pair(Parser::symbols_[18], Parser::symbols_[7]), Parser::productions_[17]},
                                                                                                                 {std::make_pair(Parser::symbols_[18], Parser::symbols_[8]), Parser::productions_[17]},
                                                                                                                 {std::make_pair(Parser::symbols_[18], Parser::symbols_[10]), Parser::productions_[17]},
                                                                                                                 {std::make_pair(Parser::symbols_[18], Parser::symbols_[16]), Parser::productions_[15]},
                                                                                                                 {std::make_pair(Parser::symbols_[18], Parser::symbols_[21]), Parser::productions_[17]},
        // STS
                                                                                                                 {std::make_pair(Parser::symbols_[19], Parser::symbols_[7]), Parser::productions_[18]},
                                                                                                                 {std::make_pair(Parser::symbols_[19], Parser::symbols_[8]), Parser::productions_[18]},
                                                                                                                 {std::make_pair(Parser::symbols_[19], Parser::symbols_[10]), Parser::productions_[18]},
                                                                                                                 {std::make_pair(Parser::symbols_[19], Parser::symbols_[21]), Parser::productions_[19]},
};

void Parser::parse ()
{
    TokenPtr token = scanner_->getToken();
    SymbolPtr input;

    while (!scanner_->endReached())
    {
        input = mapTokenToSymbol(token);
        if (input == stack_.top())
            accept();
        else if (!stack_.top()->isTerminal())
            derive();
        else
            logError();

        token = scanner_->getToken();
    }
}

Parser::SymbolPtr Parser::mapTokenToSymbol(TokenPtr token)
{

}

void Parser::accept ()
{

}

void Parser::derive()
{

}

void Parser::logError ()
{

}