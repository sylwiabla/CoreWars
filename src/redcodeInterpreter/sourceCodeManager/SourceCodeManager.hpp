//
// Created by sylwia on 4/18/17.
//

#ifndef REDCODEINTERPRETER_SOURCECODEMANAGER_HPP
#define REDCODEINTERPRETER_SOURCECODEMANAGER_HPP

#include <fstream>
#include <boost/filesystem.hpp>
#include "exceptions/SourceFileNotFound.hpp"

class SourceCodeManager
{
public:
    SourceCodeManager (std::string fileName) : fileName_(fileName)
    {
        opened_ = false;
    }

    ~SourceCodeManager ()
    {
        fin_.close();
    }

    int getNext();
    void openFile();

private:
    std::string fileName_;
    std::ifstream fin_;
    bool opened_;

};

#endif //REDCODEINTERPRETER_SOURCECODEMANAGER_HPP
