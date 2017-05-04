//
// Created by sylwia on 4/18/17.
//

#ifndef REDCODEINTERPRETER_PARSER_HPP
#define REDCODEINTERPRETER_PARSER_HPP

#include <memory>
#include <list>
#include "../errorLogger/ErrorLogger.hpp"
#include "../symbol/AddressingMode.hpp"
#include "../symbol/Modifier.hpp"
#include "../symbol/PseudoInstruction.hpp"
#include "../symbol/identifier/Label.hpp"
#include "../symbol/identifier/NumericValue.hpp"
#include "../symbol/instruction/OneArgsInstruction.hpp"
#include "../symbol/instruction/TwoArgsInstruction.hpp"
#include "../symbol/instruction/ZeroArgsInstruction.hpp"

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
