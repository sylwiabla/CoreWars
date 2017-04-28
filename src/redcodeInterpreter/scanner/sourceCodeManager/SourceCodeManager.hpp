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
    SourceCodeManager () : opened_(false), endReached_(false), fileName_(""), lineNr_(0)
    {}

    SourceCodeManager (const std::string & fileName) : fileName_(fileName)
    {
        opened_ = false;
        endReached_ = false;
        lineNr_ = 0;
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
        char c = fin_.get();
        if(c == '\n')
            --lineNr_;
        fin_.unget();
    }

    void setFilename (const std::string filename)
    {
        fileName_ = filename;
    }

    inline std::string getFilename () const
    {
        return fileName_;
    }

    inline unsigned int getLineNr () const
    {
        return lineNr_;
    }

private:
    std::string fileName_;
    std::ifstream fin_;
    bool opened_;
    bool endReached_;
    unsigned int lineNr_;
    boost::mutex readMutex_;

    static const char DEFAULT_CHAR = '\0';

    void openFile();

};

typedef std::shared_ptr<SourceCodeManager> SourceManagerPtr;

#endif //REDCODEINTERPRETER_SOURCECODEMANAGER_HPP
