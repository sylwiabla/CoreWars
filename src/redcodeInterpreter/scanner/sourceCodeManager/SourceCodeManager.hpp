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
    SourceCodeManager () : endReached_(false), lineNr_(0)
    {}

    virtual char getNext()
    {
        return DEFAULT_CHAR;
    }
    virtual bool endReached () const
    {
        return true;
    }
    virtual void unget()
    {}

    inline unsigned int getLineNr () const
    {
        return lineNr_;
    }

protected:
    bool endReached_;
    unsigned int lineNr_;
    boost::mutex readMutex_;

    static const char DEFAULT_CHAR = '\0';
};

typedef std::shared_ptr<SourceCodeManager> SourceManagerPtr;

#endif //REDCODEINTERPRETER_SOURCECODEMANAGER_HPP
