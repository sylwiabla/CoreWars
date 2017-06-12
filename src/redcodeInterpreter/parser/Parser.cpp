//
// Created by Sylwia Blach on 4/18/17.
//

#include "Parser.hpp"

const Parser::Terminals Parser::terminals_ = {{Token::immidiateMode, addMode}, {Token::directMode, addMode}, {Token::indirectMode, addMode}, {Token::AModifier, mod}, {Token::BModifier, mod}, {Token::ABModifier, mod},
                                        {Token::BAModifier, mod}, {Token::FModifier, mod}, {Token::XModifier, mod}, {Token::IModifier, mod}, {Token::equ, equ}, {Token::forType, forType},
                                        {Token::rof, rof}, {Token::dat, inst2}, {Token::mov, inst2}, {Token::add, inst2}, {Token::sub, inst2}, {Token::mul, inst2}, {Token::div, inst2}, {Token::mod, inst2},
                                        {Token::jmz, inst2}, {Token::jmn, inst2}, {Token::djn, inst2}, {Token::spl, inst2}, {Token::cmp, inst2}, {Token::seq, inst2}, {Token::sne, inst2}, {Token::slt, inst2},
                                        {Token::ldp, inst2}, {Token::stp, inst2}, {Token::jmp, inst1}, {Token::nop, inst0}, {Token::comma, comma}, {Token::numeric, numeric}, {Token::alpha, label},
                                        {Token::dot, dot}, {Token::uqe, uqe},};

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
const std::vector<Parser::SymbolPtr> Parser::equVNumRule = {Parser::symbols_[20], Parser::symbols_[16]};
const std::vector<Parser::SymbolPtr> Parser::equVLabRule = {Parser::symbols_[20], Parser::symbols_[6]};
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
Parser::PredictTable Parser::predictTable_ = {{std::make_pair(*Parser::symbols_[0], *Parser::symbols_[6]), Parser::productions_[0]},
                                              {std::make_pair(*Parser::symbols_[0], *Parser::symbols_[7]), Parser::productions_[0]},
                                              {std::make_pair(*Parser::symbols_[0], *Parser::symbols_[8]), Parser::productions_[0]},
                                              {std::make_pair(*Parser::symbols_[0], *Parser::symbols_[10]), Parser::productions_[0]},
                                              {std::make_pair(*Parser::symbols_[0], *Parser::symbols_[21]), Parser::productions_[0]},
                                              {std::make_pair(*Parser::symbols_[0], *Parser::symbols_[22]), Parser::productions_[1]},
                                              {std::make_pair(*Parser::symbols_[0], *Parser::symbols_[17]), Parser::productions_[0]},
                                              {std::make_pair(*Parser::symbols_[0], *Parser::symbols_[20]), Parser::productions_[1]},
                                              {std::make_pair(*Parser::symbols_[0], *Parser::symbols_[25]), Parser::productions_[1]},
        // STAT
                                              {std::make_pair(*Parser::symbols_[1], *Parser::symbols_[6]), Parser::productions_[5]},
                                              {std::make_pair(*Parser::symbols_[1], *Parser::symbols_[7]), Parser::productions_[2]},
                                              {std::make_pair(*Parser::symbols_[1], *Parser::symbols_[8]), Parser::productions_[2]},
                                              {std::make_pair(*Parser::symbols_[1], *Parser::symbols_[10]), Parser::productions_[2]},
                                              {std::make_pair(*Parser::symbols_[1], *Parser::symbols_[21]), Parser::productions_[4]},
                                              {std::make_pair(*Parser::symbols_[1], *Parser::symbols_[17]), Parser::productions_[3]},
        // INST
                                              {std::make_pair(*Parser::symbols_[3], *Parser::symbols_[7]), Parser::productions_[6]},
                                              {std::make_pair(*Parser::symbols_[3], *Parser::symbols_[8]), Parser::productions_[7]},
                                              {std::make_pair(*Parser::symbols_[3], *Parser::symbols_[10]), Parser::productions_[8]},
        // OP
                                              {std::make_pair(*Parser::symbols_[9], *Parser::symbols_[6]), Parser::productions_[10]},
                                              {std::make_pair(*Parser::symbols_[9], *Parser::symbols_[12]), Parser::productions_[9]},
                                              {std::make_pair(*Parser::symbols_[9], *Parser::symbols_[16]), Parser::productions_[10]},
        // OP1
                                              {std::make_pair(*Parser::symbols_[13], *Parser::symbols_[6]), Parser::productions_[11]},
                                              {std::make_pair(*Parser::symbols_[13], *Parser::symbols_[16]), Parser::productions_[11]},
        // MOD
                                              {std::make_pair(*Parser::symbols_[15], *Parser::symbols_[6]), Parser::productions_[22]},
                                              {std::make_pair(*Parser::symbols_[15], *Parser::symbols_[7]), Parser::productions_[22]},
                                              {std::make_pair(*Parser::symbols_[15], *Parser::symbols_[8]), Parser::productions_[22]},
                                              {std::make_pair(*Parser::symbols_[15], *Parser::symbols_[10]), Parser::productions_[22]},
                                              {std::make_pair(*Parser::symbols_[15], *Parser::symbols_[11]), Parser::productions_[22]},
                                              {std::make_pair(*Parser::symbols_[15], *Parser::symbols_[23]), Parser::productions_[21]},
                                              {std::make_pair(*Parser::symbols_[15], *Parser::symbols_[21]), Parser::productions_[22]},
                                              {std::make_pair(*Parser::symbols_[15], *Parser::symbols_[22]), Parser::productions_[22]},
                                              {std::make_pair(*Parser::symbols_[15], *Parser::symbols_[17]), Parser::productions_[22]},
                                              {std::make_pair(*Parser::symbols_[15], *Parser::symbols_[20]), Parser::productions_[22]},
                                              {std::make_pair(*Parser::symbols_[15], *Parser::symbols_[25]), Parser::productions_[22]},
        // OP_NAME
                                              {std::make_pair(*Parser::symbols_[14], *Parser::symbols_[6]), Parser::productions_[13]},
                                              {std::make_pair(*Parser::symbols_[14], *Parser::symbols_[16]), Parser::productions_[12]},
        // FOR
                                              {std::make_pair(*Parser::symbols_[5], *Parser::symbols_[21]), Parser::productions_[20]},
        // EQU
                                              {std::make_pair(*Parser::symbols_[4], *Parser::symbols_[17]), Parser::productions_[14]},
        // EQU_VAL
                                              {std::make_pair(*Parser::symbols_[18], *Parser::symbols_[6]), Parser::productions_[16]},
                                              {std::make_pair(*Parser::symbols_[18], *Parser::symbols_[7]), Parser::productions_[17]},
                                              {std::make_pair(*Parser::symbols_[18], *Parser::symbols_[8]), Parser::productions_[17]},
                                              {std::make_pair(*Parser::symbols_[18], *Parser::symbols_[10]), Parser::productions_[17]},
                                              {std::make_pair(*Parser::symbols_[18], *Parser::symbols_[16]), Parser::productions_[15]},
                                              {std::make_pair(*Parser::symbols_[18], *Parser::symbols_[21]), Parser::productions_[17]},
        // STS
                                              {std::make_pair(*Parser::symbols_[19], *Parser::symbols_[7]), Parser::productions_[18]},
                                              {std::make_pair(*Parser::symbols_[19], *Parser::symbols_[8]), Parser::productions_[18]},
                                              {std::make_pair(*Parser::symbols_[19], *Parser::symbols_[10]), Parser::productions_[18]},
                                              {std::make_pair(*Parser::symbols_[19], *Parser::symbols_[21]), Parser::productions_[19]} };

CodePtr Parser::parse ()
{
    TokenPtr token = scanner_->getToken();
    SymbolPtr input;

    while (!scanner_->endReached() && !logger_->isFull())
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
            derive(input);
        else
        {
            logError();
            token = scanner_->getToken();
        }
    }
    return std::make_shared<Code> (code_);
}

Parser::SymbolPtr Parser::mapTokenToSymbol (TokenPtr token)
{
    auto iter = terminals_.find(token->getType());
    bool isTerminal = (iter != terminals_.end());
    std::shared_ptr<Symbol> symbol = std::make_shared<Symbol> (isTerminal, iter->second);
    return symbol;
}

void Parser::accept (TokenPtr token, SymbolType type)
{
    stack_.pop();

    if ((type == inst0) || (type == inst1) || (type == inst2))
        acceptInst(token->getType(), type);
    else if (type == addMode)
        acceptAddrMode(token->getType());
    else if (type == numeric)
        acceptNumeric(token->getName());
    else if ((type == equ) || (type == forType))
        acceptComposite(token->getType());
    else if (type == mod)
        acceptModifier(token->getType());
    else if (type == rof)
        acceptRof();
    else if (type == uqe)
        acceptUqe();
    else if (type == label)
        acceptLabel(token->getName());
}

void Parser::derive(SymbolPtr input)
{
    std::pair<Symbol, Symbol> pair = std::make_pair(*stack_.top(), *input);
    auto production = predictTable_.find(pair);
    stack_.pop();

    if (production == predictTable_.end())
        logError();
    else
        for (SymbolPtr symbol : production->second->getDerivation())
            stack_.push(symbol);
}

void Parser::logError () // @TODO
{
    logger_->logError(std::make_shared<Error> (Error (scanner_->getLineNr(), "Unexpected identifier")));
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

void Parser::acceptAddrMode(Token::TokenType type)
{
    if (nestedInstructions_.empty())
        code_.back()->insertAddrMode(type);
    else
    {
        CompInstPtr parentInstruction;
        parentInstruction = nestedInstructions_.top();
        parentInstruction->insertAddrMode(type);
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

void Parser::acceptModifier (Token::TokenType type)
{
    if (nestedInstructions_.empty())
        code_.back()->insertModifier(type);
    else
    {
        CompInstPtr parentInstruction;
        parentInstruction = nestedInstructions_.top();
        parentInstruction->insertModifier(type);
    }
}

void Parser::acceptComposite (Token::TokenType type)
{
    CompInstPtr compositeInstruction = std::make_shared<CompositeInstruction> (type);
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