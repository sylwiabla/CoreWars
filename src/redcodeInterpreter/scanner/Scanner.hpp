//
// Created by Sylwia Blach on 4/19/17.
//

#ifndef REDCODEINTERPRETER_SCANNER_HPP
#define REDCODEINTERPRETER_SCANNER_HPP

#include <unordered_map>
#include "sourceCodeManager/SourceCodeManager.hpp"
#include "../errorLogger/ErrorLogger.hpp"
#include "token/Token.hpp"

class Scanner
{
public:
    Scanner(SourceManagerPtr sourceManagerPtr, const ErrorLoggerPtr & logger) : logger_(logger), sourceCodeManager_(std::move(sourceManagerPtr))
    {}

    typedef const std::unordered_map<std::string, Token::Type> Keywords;

private:
    static const unsigned int MAX_IDENTIFIER_LENGTH = 1024;

    SourceManagerPtr sourceCodeManager_;
    ErrorLoggerPtr logger_;

    static Keywords keywords_;
    static const char COMMENT_START = ';';

public:
    TokenPtr getToken();
    inline bool endReached () const
    {
        return sourceCodeManager_->endReached();
    }
    inline unsigned int getLineNr () const
    {
        return sourceCodeManager_->getLineNr();
    }

    typedef Keywords::const_iterator KeywordIter;

private:
    void omitComment ();
    void omitWhiteSpace ();
    TokenPtr createToken (char first);
    TokenPtr createNumeric (char first);
    TokenPtr createAlpha (char first);
    TokenPtr createOther (char first);

};

typedef std::unique_ptr<Scanner> ScannerPtr;

#endif //REDCODEINTERPRETER_SCANNER_HPP
