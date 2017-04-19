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
        cnvt_.str("");

        cnvt_ << std::runtime_error::what() << ": " << "Source file not found";

        return cnvt_.str().c_str();
    }

private:
    static std::ostringstream cnvt_;
};

#endif //REDCODEINTERPRETER_SOURCEFILENOTFOUND_HPP
