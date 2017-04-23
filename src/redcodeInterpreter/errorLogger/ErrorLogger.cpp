//
// Created by Sylwia Blach on 4/23/17.
//

#include "ErrorLogger.hpp"

void ErrorLogger::logError(const Error & error)
{
    boost::mutex::scoped_lock scoped_lock(writeMutex_);
    errorQueue_.push(error);
    std::cout << "Line: " << error.first << " " << error.second << std::endl;
}

Error * ErrorLogger::getError ()
{
    boost::mutex::scoped_lock scoped_lock(readMutex_);

    if (errorQueue_.empty())
        return nullptr;

    unsigned int lineNr = errorQueue_.front().first;
    std::string * message = new std::string (errorQueue_.front().second);
    Error * result = new Error (static_cast<unsigned int &&> (lineNr), static_cast<std::string &&> (*message));
    errorQueue_.pop();
    return result;
};