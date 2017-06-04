//
// Created by sylwia on 5/5/17.
//

#ifndef REDCODEINTERPRETER_FILESYSTEMSOURCEMANAGER_HPP
#define REDCODEINTERPRETER_FILESYSTEMSOURCEMANAGER_HPP

#include "SourceCodeManager.hpp"

class FilesystemSourceManager : public SourceCodeManager
{
public:
    FilesystemSourceManager () : SourceCodeManager(), fileName_("")
    {
        init();
    }

    FilesystemSourceManager (const std::string & fileName) : SourceCodeManager (), fileName_(fileName)
    {
        init();
    }

    ~FilesystemSourceManager()
    {
        fin_.close();
    }

    void init ();

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

    void openFile ();
};

typedef std::unique_ptr<FilesystemSourceManager> FilesystemManagerPtr;

#endif //REDCODEINTERPRETER_FILESYSTEMSOURCEMANAGER_HPP
