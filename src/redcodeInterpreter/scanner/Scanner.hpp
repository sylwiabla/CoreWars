//
// Created by Sylwia Blach on 4/19/17.
//

#ifndef REDCODEINTERPRETER_SCANNER_HPP
#define REDCODEINTERPRETER_SCANNER_HPP

#include "sourceCodeManager/SourceCodeManager.hpp"
#include "../errorLogger/ErrorLogger.hpp"
#include "../token/Token.hpp"

class Scanner
{
public:
    Scanner(const std::string & filename, ErrorLoggerPtr logger) : logger_(logger)
    {
        sourceCodeManager_ = std::make_shared<SourceCodeManager> (filename);
    }

private:
    static const unsigned int MAX_IDENTIFIER_LENGTH = 1024;

    SourceManagerPtr sourceCodeManager_;
    ErrorLoggerPtr logger_;

public:
    TokenPtr getToken();
    inline bool endReached () const
    {
        return sourceCodeManager_->endReached();
    }

private:
    void omitComment ();
    void omitWhiteSpace ();
    TokenPtr createToken (char first);
    TokenPtr createNumeric (char first);
    TokenPtr createAlpha (char first);
    TokenPtr createOther (char first);

};

typedef std::shared_ptr<Scanner> ScannerPtr;

#endif //REDCODEINTERPRETER_SCANNER_HPP
