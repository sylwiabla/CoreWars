//
// Created by Sylwia Blach on 4/23/17.
//

#include "ErrorLogger.hpp"

void ErrorLogger::logError(const ErrorPtr & error)
{
    boost::mutex::scoped_lock scoped_lock(writeMutex_);
    errorQueue_.push(error);
}

ErrorPtr ErrorLogger::getError ()
{
    boost::mutex::scoped_lock scoped_lock(readMutex_);

    if (errorQueue_.empty())
        return nullptr;

    Error error = *errorQueue_.front();

    unsigned int lineNr = std::get<0> (static_cast<Error &&> (error));
    std::string message = std::get<1> (static_cast<Error &&> (error));
    ErrorPtr result = std::make_shared<Error> (lineNr, message);
    errorQueue_.pop();
    return result;
};