//
// Created by sylwia on 6/8/17.
//

#ifndef REDCODEINTERPRETER_OUTOFMEMORY_HPP
#define REDCODEINTERPRETER_OUTOFMEMORY_HPP

#include <exception>
#include <stdexcept>
#include <sstream>

class OutOfMemory : public std::runtime_error {
public:
    OutOfMemory()
            : std::runtime_error("Out of memory")
    {}

    virtual const char* what() const throw()
    {
        return "Out of memory - there was an attempt to load too big source file";
    }
};

#endif //REDCODEINTERPRETER_OUTOFMEMORY_HPP
