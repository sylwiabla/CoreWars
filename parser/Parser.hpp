//
// Created by sylwia on 4/18/17.
//

#ifndef REDCODEINTERPRETER_PARSER_HPP
#define REDCODEINTERPRETER_PARSER_HPP

#include "GrammarRulesSet.hpp"

class Parser
{
public:
    static Parser & getInstance()
    {
        static Parser instance;
        return instance;
    }

private:
    Parser()
    {}

    Parser (Parser const&) = delete;
    void operator=(Parser const&) = delete;

public:
    std::set<RulePtr> * parse ();



}


#endif //REDCODEINTERPRETER_PARSER_HPP
