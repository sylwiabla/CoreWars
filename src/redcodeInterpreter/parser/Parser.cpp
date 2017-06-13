//
// Created by Sylwia Blach on 4/18/17.
//

#include "Parser.hpp"

const Parser::Terminals Parser::terminals_ = {{Token::immediateMode, addMode}, {Token::directMode, addMode}, {Token::indirectMode, addMode}, {Token::AModifier, mod}, {Token::BModifier, mod}, {Token::ABModifier, mod},
                                              {Token::BAModifier, mod}, {Token::FModifier, mod}, {Token::XModifier, mod}, {Token::IModifier, mod}, {Token::equ, equ}, {Token::forType, forType},
                                              {Token::rof, rof}, {Token::dat, inst2}, {Token::mov, inst2}, {Token::add, inst2}, {Token::sub, inst2}, {Token::mul, inst2}, {Token::div, inst2}, {Token::mod, inst2},
                                              {Token::jmz, inst2}, {Token::jmn, inst2}, {Token::djn, inst2}, {Token::spl, inst2}, {Token::cmp, inst2}, {Token::seq, inst2}, {Token::sne, inst2}, {Token::slt, inst2},
                                              {Token::jmp, inst1}, {Token::nop, inst0}, {Token::comma, comma}, {Token::numeric, numeric}, {Token::alpha, label}, {Token::dot, dot}, {Token::uqe, uqe},};

const Parser::Derivation Parser::statsStatRule = {std::make_shared<Symbol> (false, STATS), std::make_shared<Symbol> (false, STAT)};
const Parser::Derivation Parser::statsEpsRule = {std::make_shared<Symbol> (true, epsilon)};
const Parser::Derivation Parser::statInstRule = {std::make_shared<Symbol> (false, INST)};
const Parser::Derivation Parser::statEquRule = {std::make_shared<Symbol> (false, EQU)};
const Parser::Derivation Parser::statForRule = {std::make_shared<Symbol> (false, FOR)};
const Parser::Derivation Parser::statLabRule = {std::make_shared<Symbol> (true, label)};
const Parser::Derivation Parser::instInst0Rule = {std::make_shared<Symbol> (true, inst0)};
const Parser::Derivation Parser::instInst1Rule = {std::make_shared<Symbol> (false, OP), std::make_shared<Symbol> (true, inst1)};
const Parser::Derivation Parser::instInst2Rule = {std::make_shared<Symbol> (false, OP), std::make_shared<Symbol> (true, comma), std::make_shared<Symbol> (false, OP), std::make_shared<Symbol> (true, inst2)};
const Parser::Derivation Parser::opAddRule = {std::make_shared<Symbol> (false, OP1), std::make_shared<Symbol> (true, addMode)};
const Parser::Derivation Parser::opOp1Rule = {std::make_shared<Symbol> (false, OP1)};
const Parser::Derivation Parser::op1Rule = {std::make_shared<Symbol> (false, MOD), std::make_shared<Symbol> (false, OP_NAME)};
const Parser::Derivation Parser::opNameNumRule = {std::make_shared<Symbol> (true, numeric)};
const Parser::Derivation Parser::opNameLabRule = {std::make_shared<Symbol> (true, label)};
const Parser::Derivation Parser::equRule = {std::make_shared<Symbol> (false, EQU_VAL), std::make_shared<Symbol> (true, label), std::make_shared<Symbol> (true, equ)};
const Parser::Derivation Parser::equVNumRule = {std::make_shared<Symbol> (true, uqe), std::make_shared<Symbol> (true, numeric)};
const Parser::Derivation Parser::equVLabRule = {std::make_shared<Symbol> (true, uqe), std::make_shared<Symbol> (true, label)};
const Parser::Derivation Parser::equVStsRule = {std::make_shared<Symbol> (true, uqe), std::make_shared<Symbol> (false, STS)};
const Parser::Derivation Parser::stsInstRule = {std::make_shared<Symbol> (false, STATS), std::make_shared<Symbol> (false, INST)};
const Parser::Derivation Parser::stsForRule = {std::make_shared<Symbol> (false, STATS), std::make_shared<Symbol> (false, FOR)};
const Parser::Derivation Parser::forRule = {std::make_shared<Symbol> (true, rof), std::make_shared<Symbol> (false, STS), std::make_shared<Symbol> (false, OP_NAME), std::make_shared<Symbol> (true, forType)};
const Parser::Derivation Parser::modDotRule = {std::make_shared<Symbol> (true, mod), std::make_shared<Symbol> (true, dot)};
const Parser::Derivation Parser::modEpsRule = {std::make_shared<Symbol> (true, epsilon)};

const std::vector<Parser::ProductionPtr> Parser::productions_ = {std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, STATS), Parser::statsStatRule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, STATS), Parser::statsEpsRule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, STAT), Parser::statInstRule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, STAT), Parser::statEquRule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, STAT), Parser::statForRule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, STAT), Parser::statLabRule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, INST), Parser::instInst0Rule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, INST), Parser::instInst1Rule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, INST), Parser::instInst2Rule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, OP), Parser::opAddRule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, OP), Parser::opOp1Rule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, OP1), Parser::op1Rule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, OP_NAME), Parser::opNameNumRule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, OP_NAME), Parser::opNameLabRule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, EQU), Parser::equRule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, EQU_VAL), Parser::equVNumRule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, EQU_VAL), Parser::equVLabRule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, EQU_VAL), Parser::equVStsRule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, EQU_VAL), Parser::stsInstRule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, EQU_VAL), Parser::stsForRule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, FOR), Parser::forRule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, MOD), Parser::modDotRule),
                                                                 std::make_shared<ProductionRule> (std::make_shared<Symbol> (false, MOD), Parser::modEpsRule)};

// STATS
Parser::PredictTable Parser::predictTable_ = {{std::make_pair(*std::make_shared<Symbol> (false, STATS), *std::make_shared<Symbol> (true, label)), Parser::productions_[0]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, STATS), *std::make_shared<Symbol> (true, inst0)), Parser::productions_[0]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, STATS), *std::make_shared<Symbol> (true, inst1)), Parser::productions_[0]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, STATS), *std::make_shared<Symbol> (true, inst2)), Parser::productions_[0]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, STATS), *std::make_shared<Symbol> (true, forType)), Parser::productions_[0]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, STATS), *std::make_shared<Symbol> (true, rof)), Parser::productions_[1]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, STATS), *std::make_shared<Symbol> (true, equ)), Parser::productions_[0]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, STATS), *std::make_shared<Symbol> (true, uqe)), Parser::productions_[1]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, STATS), *std::make_shared<Symbol> (true, end)), Parser::productions_[1]},
        // STAT
                                              {std::make_pair(*std::make_shared<Symbol> (false, STAT), *std::make_shared<Symbol> (true, label)), Parser::productions_[5]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, STAT), *std::make_shared<Symbol> (true, inst0)), Parser::productions_[2]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, STAT), *std::make_shared<Symbol> (true, inst1)), Parser::productions_[2]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, STAT), *std::make_shared<Symbol> (true, inst2)), Parser::productions_[2]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, STAT), *std::make_shared<Symbol> (true, forType)), Parser::productions_[4]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, STAT), *std::make_shared<Symbol> (true, equ)), Parser::productions_[3]},
        // INST
                                              {std::make_pair(*std::make_shared<Symbol> (false, INST), *std::make_shared<Symbol> (true, inst0)), Parser::productions_[6]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, INST), *std::make_shared<Symbol> (true, inst1)), Parser::productions_[7]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, INST), *std::make_shared<Symbol> (true, inst2)), Parser::productions_[8]},
        // OP
                                              {std::make_pair(*std::make_shared<Symbol> (false, OP), *std::make_shared<Symbol> (true, label)), Parser::productions_[10]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, OP), *std::make_shared<Symbol> (true, addMode)), Parser::productions_[9]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, OP), *std::make_shared<Symbol> (true, numeric)), Parser::productions_[10]},
        // OP1
                                              {std::make_pair(*std::make_shared<Symbol> (false, OP1), *std::make_shared<Symbol> (true, label)), Parser::productions_[11]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, OP1), *std::make_shared<Symbol> (true, numeric)), Parser::productions_[11]},
        // MOD
                                              {std::make_pair(*std::make_shared<Symbol> (false, MOD), *std::make_shared<Symbol> (true, label)), Parser::productions_[22]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, MOD), *std::make_shared<Symbol> (true, inst0)), Parser::productions_[22]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, MOD), *std::make_shared<Symbol> (true, inst1)), Parser::productions_[22]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, MOD), *std::make_shared<Symbol> (true, inst2)), Parser::productions_[22]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, MOD), *std::make_shared<Symbol> (true, comma)), Parser::productions_[22]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, MOD), *std::make_shared<Symbol> (true, dot)), Parser::productions_[21]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, MOD), *std::make_shared<Symbol> (true, forType)), Parser::productions_[22]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, MOD), *std::make_shared<Symbol> (true, rof)), Parser::productions_[22]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, MOD), *std::make_shared<Symbol> (true, equ)), Parser::productions_[22]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, MOD), *std::make_shared<Symbol> (true, uqe)), Parser::productions_[22]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, MOD), *std::make_shared<Symbol> (true, end)), Parser::productions_[22]},
        // OP_NAME
                                              {std::make_pair(*std::make_shared<Symbol> (false, OP_NAME), *std::make_shared<Symbol> (true, label)), Parser::productions_[13]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, OP_NAME), *std::make_shared<Symbol> (true, numeric)), Parser::productions_[12]},
        // FOR
                                              {std::make_pair(*std::make_shared<Symbol> (false, FOR), *std::make_shared<Symbol> (true, forType)), Parser::productions_[20]},
        // EQU
                                              {std::make_pair(*std::make_shared<Symbol> (false, EQU), *std::make_shared<Symbol> (true, equ)), Parser::productions_[14]},
        // EQU_VAL
                                              {std::make_pair(*std::make_shared<Symbol> (false, EQU_VAL), *std::make_shared<Symbol> (true, label)), Parser::productions_[16]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, EQU_VAL), *std::make_shared<Symbol> (true, inst0)), Parser::productions_[17]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, EQU_VAL), *std::make_shared<Symbol> (true, inst1)), Parser::productions_[17]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, EQU_VAL), *std::make_shared<Symbol> (true, inst2)), Parser::productions_[17]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, EQU_VAL), *std::make_shared<Symbol> (true, numeric)), Parser::productions_[15]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, EQU_VAL), *std::make_shared<Symbol> (true, forType)), Parser::productions_[17]},
        // STS
                                              {std::make_pair(*std::make_shared<Symbol> (false, STS), *std::make_shared<Symbol> (true, inst0)), Parser::productions_[18]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, STS), *std::make_shared<Symbol> (true, inst1)), Parser::productions_[18]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, STS), *std::make_shared<Symbol> (true, inst2)), Parser::productions_[18]},
                                              {std::make_pair(*std::make_shared<Symbol> (false, STS), *std::make_shared<Symbol> (true, forType)), Parser::productions_[19]} };

CodePtr Parser::parse ()
{
    TokenPtr token = scanner_->getToken();
    SymbolPtr input;

    while (token && !logger_->isFull())
    {
        while (!token)
            token = scanner_->getToken();

        while (stack_.top()->getType() == epsilon)
            stack_.pop();

        input = mapTokenToSymbol(token);
        if (*input == *stack_.top())
        {
            accept(token, input->getType());
            token = scanner_->getToken();
        }
        else if (!stack_.top()->isTerminal())
            derive(token->getType(), input);
        else
        {
            logError(token->getType());
            token = scanner_->getToken();
        }
    }
    return std::make_shared<Code> (code_);
}

Parser::SymbolPtr Parser::mapTokenToSymbol (TokenPtr token)
{
    auto iter = terminals_.find(token->getType().getTokenType());
    bool isTerminal = (iter != terminals_.end());
    std::shared_ptr<Symbol> symbol = std::make_shared<Symbol> (isTerminal, iter->second);
    return symbol;
}

void Parser::accept (TokenPtr token, SymbolType type)
{
    stack_.pop();

    if ((type == inst0) || (type == inst1) || (type == inst2))
        acceptInst(token->getType().getTokenType(), type);
    else if (type == addMode)
        acceptAddrMode(token->getType());
    else if (type == numeric)
        acceptNumeric(token->getValue());
    else if ((type == equ) || (type == forType))
        acceptComposite(token->getType());
    else if (type == mod)
        acceptModifier(token->getType());
    else if (type == rof)
        acceptRof();
    else if (type == uqe)
        acceptUqe();
    else if (type == label)
        acceptLabel(token->getValue());
}

void Parser::derive(Token::Type type, SymbolPtr input)
{
    std::pair<Symbol, Symbol> pair = std::make_pair(*stack_.top(), *input);
    auto production = predictTable_.find(pair);
    stack_.pop();

    if (production == predictTable_.end())
        logError(type);
    else
        for (SymbolPtr symbol : production->second->getDerivation())
            stack_.push(symbol);
}

void Parser::logError (Token::Type type)
{
    logger_->logError(std::make_shared<Error> (Error (scanner_->getLineNr(), "Unexpected identifier of type " + type.getName())));
}

const InstructionPtr Parser::acceptInst (Token::TokenType tokenType, SymbolType symbolType)
{
    InstructionPtr instruction;
    if (symbolType == inst0)
        instruction = std::make_shared<ZeroArgsInstruction> (tokenType);
    else if (symbolType == inst1)
        instruction = std::make_shared<OneArgsInstruction> (tokenType);
    else
        instruction = std::make_shared<TwoArgsInstruction> (tokenType);

    if (nestedInstructions_.empty())
        code_.push_back(instruction);
    else
    {
        CompInstPtr parentInstruction;
        parentInstruction = nestedInstructions_.top();
        parentInstruction->insertInstruction(instruction, nestedInstructions_.top());
    }
    return  instruction;
}

void Parser::acceptAddrMode(Token::Type type)
{
    if (nestedInstructions_.empty())
        code_.back()->insertAddrMode(type.getTokenType());
    else
    {
        CompInstPtr parentInstruction;
        parentInstruction = nestedInstructions_.top();
        parentInstruction->insertAddrMode(type.getTokenType());
    }
}

void Parser::acceptNumeric (std::string value)
{
    try
    {
        long numValue = boost::lexical_cast<long> (value);
        if (nestedInstructions_.empty())
            code_.back()->insertNumeric(numValue);
        else
        {
            CompInstPtr parentInstruction;
            parentInstruction = nestedInstructions_.top();
            std::string recentlyAdded = symbolTableManager_->getRecentlyAdded();
            if (recentlyAdded == "")
                parentInstruction->insertNumeric(numValue);
            else
            {
                if (parentInstruction->needsNumeric())
                    parentInstruction->insertNumeric(numValue);
                else
                {
                    symbolTableManager_->insert(recentlyAdded, std::make_shared<Label> (recentlyAdded, numValue));
                    symbolTableManager_->setRecentlyAdded("");
                }
            }
        }
    }
    catch (const std::invalid_argument & e)
    {
        logger_->logError(std::make_shared<Error> (Error (scanner_->getLineNr(), "Invalid address: " + value)));
    }
    catch (const std::out_of_range & e)
    {
        logger_->logError(std::make_shared<Error> (Error (scanner_->getLineNr(), "Address out of range: " + value)));
    }
}

void Parser::acceptModifier (Token::Type type)
{
    if (nestedInstructions_.empty())
        code_.back()->insertModifier(type.getTokenType());
    else
    {
        CompInstPtr parentInstruction;
        parentInstruction = nestedInstructions_.top();
        parentInstruction->insertModifier(type.getTokenType());
    }
}

void Parser::acceptComposite (Token::Type type)
{
    CompInstPtr compositeInstruction = std::make_shared<CompositeInstruction> (type.getTokenType());
    if (nestedInstructions_.empty())
        code_.push_back(compositeInstruction);
    else
    {
        CompInstPtr parentInstruction;
        parentInstruction = nestedInstructions_.top();
        parentInstruction->insertInstruction(compositeInstruction, nestedInstructions_.top());
    }
    nestedInstructions_.push(compositeInstruction);
}

void Parser::acceptLabel (std::string name)
{
    FunctionPtr function = symbolTableManager_->findFunction(name);
    if (function)
    {
        if (nestedInstructions_.empty())
            for (InstructionPtr instruction : function->getInstruction()->getBody())
                code_.push_back(instruction);
        else
        {
            for (InstructionPtr instruction : function->getInstruction()->getBody())
                nestedInstructions_.top()->insertInstruction(instruction, nestedInstructions_.top());
        }
    }
    else
    {
        LabelPtr label = symbolTableManager_->findLabel(name);
        if (label)
        {
            long value = label->getValue();
            if (nestedInstructions_.empty())
                code_.back()->insertNumeric(value);
            else
            {
                InstructionPtr parentInstruction = nestedInstructions_.top();
                if (parentInstruction->needsNumeric())
                    code_.back()->insertNumeric(value);
                else
                {
                    std::string recentlyAdded = symbolTableManager_->getRecentlyAdded();
                    symbolTableManager_->insert(recentlyAdded, std::make_shared<Label> (recentlyAdded, value));
                }
            }
        }
        else
        {
            if (nestedInstructions_.top()->getType() == Token::equ)
                symbolTableManager_->setRecentlyAdded(name);
            else
                logger_->logError(std::make_shared<Error> (Error (scanner_->getLineNr(), "Identifier not declared: " + name)));
        }
    }
}

void Parser::acceptUqe ()
{
    std::string recentlyAdded = symbolTableManager_->getRecentlyAdded();
    if (recentlyAdded != "")  // means that this equ invocation is procedure definition
        symbolTableManager_->insert(recentlyAdded, std::make_shared<Function> (recentlyAdded, nestedInstructions_.top()));

    code_.pop_back();        // based on grammar, function definition cannot have parent composite instruction
    nestedInstructions_.pop();
}

void Parser::acceptRof()
{
    nestedInstructions_.pop();
}