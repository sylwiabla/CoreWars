//
// Created by sylwia on 5/5/17.
//

#ifndef REDCODEINTERPRETER_FILESYSTEMSOURCEMANAGER_HPP
#define REDCODEINTERPRETER_FILESYSTEMSOURCEMANAGER_HPP

#include "SourceCodeManager.hpp"

class FilesystemSourceManager : public SourceCodeManager
{
public:
    FilesystemSourceManager () : SourceCodeManager(), opened_(false), fileName_("")
    {}

    FilesystemSourceManager (const std::string & fileName) : SourceCodeManager (), opened_(false), fileName_(fileName)
    {}

    ~FilesystemSourceManager()
    {
        fin_.close();
    }

    virtual void unget()
    {
        fin_.unget();
        char c = fin_.get();
        if(c == '\n')
            --lineNr_;
        fin_.unget();
    }
    virtual char getNext();

    virtual bool endReached () const
    {
        return endReached_;
    }

private:
    std::string fileName_;
    std::ifstream fin_;
    bool opened_;

    void openFile ();
};

typedef std::shared_ptr<FilesystemSourceManager> FilesystemManagerPtr;

#endif //REDCODEINTERPRETER_FILESYSTEMSOURCEMANAGER_HPP
