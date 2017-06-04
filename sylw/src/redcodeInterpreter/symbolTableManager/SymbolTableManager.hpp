//
// Created by Sylwia Blach on 5/11/17.
//

#ifndef REDCODEINTERPRETER_SYMBOLTABLEMANAGER_HPP
#define REDCODEINTERPRETER_SYMBOLTABLEMANAGER_HPP

#include <unordered_map>
#include "identifier/Function.hpp"
#include "identifier/Label.hpp"

class SymbolTableManager
{
public:
    SymbolTableManager ()
    {
        recentlyAdded_ = "";
    }

    FunctionPtr findFunction (std::string name)
    {
        auto iterFunc = functions_.find(name);
        if (iterFunc != functions_.end())
            return iterFunc->second;
        return nullptr;
    }

    LabelPtr findLabel (std::string name)
    {
        auto iterLabel = labels_.find(name);
        if (iterLabel != labels_.end())
            return iterLabel->second;
        return nullptr;
    }

    bool insert (std::string name, FunctionPtr identifier)
    {
        recentlyAdded_ = "";
        if (findFunction(name))
            return false;
        functions_.insert(std::make_pair(name, identifier));
        return true;
    }

    bool insert (std::string name, LabelPtr identifier)
    {
        recentlyAdded_ = "";
        if (findLabel(name))
            return false;
        labels_.insert(std::make_pair(name, identifier));
        return true;
    }

    void setRecentlyAdded (const std::string & name)
    {
        recentlyAdded_ = name;
    }

    const std::string & getRecentlyAdded () const
    {
        return recentlyAdded_;
    }

private:
    std::unordered_map<std::string, FunctionPtr> functions_;
    std::unordered_map<std::string, LabelPtr> labels_;

    std::string recentlyAdded_;     // recently recognized identifier, not assigned yet

};

typedef std::shared_ptr<SymbolTableManager> SymbolTablePtr;

#endif //REDCODEINTERPRETER_SYMBOLTABLEMANAGER_HPP
