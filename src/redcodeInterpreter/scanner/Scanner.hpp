//
// Created by Sylwia Blach on 4/19/17.
//

#ifndef REDCODEINTERPRETER_SCANNER_HPP
#define REDCODEINTERPRETER_SCANNER_HPP

#include <unordered_map>
#include "sourceCodeManager/SourceCodeManager.hpp"
#include "../errorLogger/ErrorLogger.hpp"
#include "../token/keyword/AddressingMode.hpp"
#include "../token/keyword/instruction/Instruction.hpp"
#include "../token/keyword/Modifier.hpp"
#include "../token/keyword/identifier/Label.hpp"
#include "../token/keyword/identifier/NumericValue.hpp"
#include "../RedcodeInterpreter.hpp"
//#include "sourceCodeManager/exceptions/Messages.hpp"

class Scanner
{
public:
    static Scanner & getInstance()
    {
        static Scanner instance;
        return instance;
    }

    inline void setSourceManager (const std::string & filename)
    {
        sourceCodeManager_->setFilename(filename);
    }

private:
    Scanner()
    {
        sourceCodeManager_ = std::make_shared<SourceCodeManager> ();
        lineNr_ = FIRST_LINE_NR;
        endReached_ = false;
    }

    Scanner (Scanner const&) = delete;
    void operator=(Scanner const&) = delete;

    static const std::unordered_map<char, bool> delimiters_;

    unsigned int lineNr_;
    static const unsigned int MAX_IDENTIFIER_LENGTH = 1024;
    static const unsigned int FIRST_LINE_NR = 1;
    static const char COMMENT_START = ';';

    SourceManagerPtr sourceCodeManager_;
    bool endReached_;

public:
    TokenPtr getToken();
    inline bool endReached () const
    {
        return endReached_;
    }

private:
    void omitComment ();
    void omitWhiteSpace ();
    TokenPtr createToken ();

    inline bool isDelimiter (char c)
    {
        return delimiters_.find(c) != delimiters_.end();
    }

    TokenPtr createNumToken ();
    TokenPtr createAlphaToken ();

};

typedef std::shared_ptr<Scanner> ScannerPtr;

#endif //REDCODEINTERPRETER_SCANNER_HPP
