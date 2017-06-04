//
// Created by Sylwia Blach on 4/18/17.
//

#ifndef REDCODEINTERPRETER_SOURCEFILENOTFOUND_HPP
#define REDCODEINTERPRETER_SOURCEFILENOTFOUND_HPP

#include <exception>
#include <stdexcept>
#include <sstream>

class SourceFileNotFound : public std::runtime_error {
public:
    SourceFileNotFound()
            : std::runtime_error("Source file exception")
    {}

    virtual const char* what() const throw()
    {
        return "Source file not found";
    }
};

#endif //REDCODEINTERPRETER_SOURCEFILENOTFOUND_HPP
