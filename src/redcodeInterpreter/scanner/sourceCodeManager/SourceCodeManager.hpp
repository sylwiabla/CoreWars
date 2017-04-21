//
// Created by Sylwia Blach on 4/18/17.
//

#ifndef REDCODEINTERPRETER_SOURCECODEMANAGER_HPP
#define REDCODEINTERPRETER_SOURCECODEMANAGER_HPP

#include <fstream>
#include <memory>
#include <boost/filesystem.hpp>
#include <boost/thread/mutex.hpp>
#include "exceptions/SourceFileNotFound.hpp"

class SourceCodeManager
{
public:
    SourceCodeManager () : opened_(false), endReached_(false), fileName_("")
    {}

    SourceCodeManager (const std::string & fileName) : fileName_(fileName)
    {
        opened_ = false;
        endReached_ = false;
    }

    ~SourceCodeManager ()
    {
        fin_.close();
    }

    char getNext();
    inline bool endReached () const
    {
        return endReached_;
    }
    inline void unget()
    {
        fin_.unget();
    }

    void setFilename (const std::string filename)
    {
        fileName_ = filename;
    }

private:
    std::string fileName_;
    std::ifstream fin_;
    bool opened_;
    bool endReached_;
    boost::mutex readMutex_;

    static const char DEFAULT_CHAR = '\0';

    void openFile();

};

typedef std::shared_ptr<SourceCodeManager> SourceManagerPtr;

#endif //REDCODEINTERPRETER_SOURCECODEMANAGER_HPP
