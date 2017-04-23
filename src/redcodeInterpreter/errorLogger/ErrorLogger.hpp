//
// Created by Sylwia Blach on 4/23/17.
//

#ifndef REDCODEINTERPRETER_ERRORLOGGER_HPP
#define REDCODEINTERPRETER_ERRORLOGGER_HPP

#include <iostream>
#include <queue>
#include <memory>
#include <boost/thread/mutex.hpp>

typedef std::pair<unsigned int, const std::string> Error;
typedef std::queue<Error> ErrorQueue;

class ErrorLogger
{
public:
    static ErrorLogger & getInstance()
    {
        static ErrorLogger instance;
        return instance;
    }

    ~ErrorLogger()
    {
        errorQueue_ = ErrorQueue ();
    }

    void logError(const Error &);
    Error * getError ();

private:
    ErrorLogger ()
    {}

    ErrorLogger (ErrorLogger const&) = delete;
    void operator=(ErrorLogger const&) = delete;

    ErrorQueue errorQueue_;
    boost::mutex readMutex_;
    boost::mutex writeMutex_;
};

#endif //REDCODEINTERPRETER_ERRORLOGGER_HPP
