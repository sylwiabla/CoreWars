//
// Created by Sylwia Blach on 4/23/17.
//

#ifndef REDCODEINTERPRETER_ERRORLOGGER_HPP
#define REDCODEINTERPRETER_ERRORLOGGER_HPP

#include <iostream>
#include <tuple>
#include <queue>
#include <memory>
#include <boost/thread/mutex.hpp>

typedef std::tuple<std::string, unsigned int, const std::string> Error;
typedef std::shared_ptr<Error> ErrorPtr;
typedef std::queue<ErrorPtr> ErrorQueue;

class ErrorLogger
{
public:
    ErrorLogger ()
    {}

    ~ErrorLogger()
    {
        errorQueue_ = ErrorQueue ();
    }

    void logError(ErrorPtr);
    ErrorPtr getError ();

private:
    ErrorQueue errorQueue_;
    boost::mutex readMutex_;
    boost::mutex writeMutex_;
};

typedef std::shared_ptr<ErrorLogger> ErrorLoggerPtr;

#endif //REDCODEINTERPRETER_ERRORLOGGER_HPP
