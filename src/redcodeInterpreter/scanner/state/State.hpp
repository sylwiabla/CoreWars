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
    std::string message_;

public:
    State () : isTerminal_(false), handler_(nullptr), message_("")
    {}

    State (void (*handler) ()) : handler_(handler), isTerminal_(false), message_("")
    {}

    State (bool isTerminal, void (*handler) ()) : isTerminal_(isTerminal), handler_(handler)
    {}

    void (* handler_) ();

    inline std::string getMessage () const
    {
        return message_;
    }

    inline void setMessage (const std::string & message)
    {
        message_ = message;
    }

    inline bool isTerminal () const
    {
        return isTerminal_;
    }
};

typedef std::shared_ptr<State> StatePtr;

#endif //REDCODEINTERPRETER_STATE_HPP
