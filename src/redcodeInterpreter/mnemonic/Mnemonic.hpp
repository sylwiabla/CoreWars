//
// Created by Sylwia Blach on 4/25/17.
//

#ifndef REDCODEINTERPRETER_KEYWORD_HPP
#define REDCODEINTERPRETER_KEYWORD_HPP

#include "../Token.hpp"

class Keyword : public Token
{
public:
    Keyword() {}

    void greet ();

};

typedef std::shared_ptr<Keyword> KeywordPtr;

#endif //REDCODEINTERPRETER_KEYWORD_HPP
