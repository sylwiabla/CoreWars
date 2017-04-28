//
// Created by sylwia on 4/18/17.
//

#ifndef REDCODEINTERPRETER_PARSER_HPP
#define REDCODEINTERPRETER_PARSER_HPP

#include <memory>
#include <list>
#include "../errorLogger/ErrorLogger.hpp"
#include "../mnemonic/AddressingMode.hpp"
#include "../mnemonic/Modifier.hpp"
#include "../mnemonic/PseudoInstruction.hpp"
#include "../mnemonic/identifier/Label.hpp"
#include "../mnemonic/identifier/NumericValue.hpp"
#include "../mnemonic/instruction/OneArgsInstruction.hpp"
#include "../mnemonic/instruction/TwoArgsInstruction.hpp"
#include "../mnemonic/instruction/ZeroArgsInstruction.hpp"

class Parser
{
public:
    Parser(ErrorLoggerPtr logger) : logger_(logger)
    {}

    void parse ();

private:
    ErrorLoggerPtr logger_;
    std::list<MnemonicPtr> source_;

};

typedef std::shared_ptr<Parser> ParserPtr;


#endif //REDCODEINTERPRETER_PARSER_HPP
