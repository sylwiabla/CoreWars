//
// Created by sylwia on 6/10/17.
//

#ifndef REDCODEINTERPRETER_WARRIOR_HPP
#define REDCODEINTERPRETER_WARRIOR_HPP

#include <memory>
#include <iterator>
#include <vector>

// stores process id and current pc address
typedef std::pair<int, long> Process;

class Warrior
{
private:
    std::vector<Process> processes_;
    long runningProcess_;

public:
    Warrior () : runningProcess_ (0)
    {}

    void createProcess (int processId, long pc)
    {
        processes_.push_back(std::make_pair(processId, pc));
    }

    bool killProcess_ ()
    {
        processes_.erase(processes_.begin() + runningProcess_);
        if (processes_.empty())
            return false;
        return true;
    }

    void jump (long newAddress)
    {
        if (!processes_.empty())
            processes_.begin()->second = newAddress;
    }

    long getPC () const
    {
        if (!processes_.empty())
            return processes_.begin()->second;
        return -1;
    }

    void switchProcess ()
    {
        if (!processes_.empty())
            runningProcess_ = ((++runningProcess_) % processes_.size());
    }

};

typedef std::shared_ptr<Warrior> WarriorPtr;

#endif //REDCODEINTERPRETER_WARRIOR_HPP
