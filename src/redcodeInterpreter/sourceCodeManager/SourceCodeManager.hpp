//
// Created by sylwia on 4/18/17.
//

#ifndef REDCODEINTERPRETER_SOURCECODEMANAGER_HPP
#define REDCODEINTERPRETER_SOURCECODEMANAGER_HPP

#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/thread/mutex.hpp>
#include "exceptions/SourceFileNotFound.hpp"

class SourceCodeManager
{
public:
    SourceCodeManager (std::string fileName) : fileName_(fileName)
    {
        opened_ = false;
        endReached_ = false;
    }

    ~SourceCodeManager ()
    {
        fin_.close();
    }

    char getNext();
    inline bool endReached ()
    {
        return endReached_;
    }

private:
    std::string fileName_;
    std::ifstream fin_;
    bool opened_;
    bool endReached_;
    boost::mutex readMutex_;

    void openFile();

};

#endif //REDCODEINTERPRETER_SOURCECODEMANAGER_HPP
