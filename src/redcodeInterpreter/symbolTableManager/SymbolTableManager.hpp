//
// Created by Sylwia Blach on 5/11/17.
//

#ifndef REDCODEINTERPRETER_SYMBOLTABLEMANAGER_HPP
#define REDCODEINTERPRETER_SYMBOLTABLEMANAGER_HPP

#include <unordered_map>
#include "identifier/Identifier.hpp"

class SymbolTableManager
{
public:
    SymbolTableManager ()
    {}

    IdentifierPtr find(std::string name)
    {
        auto iter = symbols_.find(name);
        if (iter != symbols_.end())
            return iter->second;
        return nullptr;
    }
    bool insert (std::string name, IdentifierPtr identifier)
    {
        if (find(name))
            return false;
        symbols_.insert(std::make_pair(name, identifier));
    }

private:
    std::unordered_map<std::string, IdentifierPtr> symbols_;

};

typedef std::shared_ptr<SymbolTableManager> SymbolTablePtr;

#endif //REDCODEINTERPRETER_SYMBOLTABLEMANAGER_HPP
