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

typedef std::tuple<unsigned int, const std::string> Error;
typedef std::shared_ptr<Error> ErrorPtr;
typedef std::queue<ErrorPtr> ErrorQueue;

class ErrorLogger
{
public:
    ErrorLogger () : nrErrors_(0)
    {}

    ~ErrorLogger()
    {
        errorQueue_ = ErrorQueue ();
    }

    void logError(const ErrorPtr &);
    ErrorPtr getError ();
    inline bool isFull () const
    {
        return nrErrors_ >= MAX_ERRORS;
    }

private:
    ErrorQueue errorQueue_;
    boost::mutex readMutex_;
    boost::mutex writeMutex_;

    unsigned int nrErrors_;
    static const unsigned int MAX_ERRORS = 1;
};

typedef std::shared_ptr<ErrorLogger> ErrorLoggerPtr;

#endif //REDCODEINTERPRETER_ERRORLOGGER_HPP
