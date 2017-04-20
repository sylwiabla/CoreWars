//
// Created by sylwia on 4/20/17.
//

#ifndef REDCODEINTERPRETER_STATE_HPP
#define REDCODEINTERPRETER_STATE_HPP

#include <memory>

class State
{
private:
    bool isTerminal_;

public:
    State () : isTerminal_(false), handler_(nullptr)
    {}

    State (void (*handler) ()) : handler_(handler), isTerminal_(false)
    {}

    State (bool isTerminal, void (*handler) ()) : isTerminal_(isTerminal), handler_(handler)
    {}

    void (* handler_) ();
};

typedef std::shared_ptr<State> StatePtr;

#endif //REDCODEINTERPRETER_STATE_HPP
