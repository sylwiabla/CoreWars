//
// Created by sylwia on 4/19/17.
//

#ifndef REDCODEINTERPRETER_SCANNER_HPP
#define REDCODEINTERPRETER_SCANNER_HPP

#include <map>
#include "sourceCodeManager/SourceCodeManager.hpp"

class Scanner
{
public:
    static Scanner & getInstance()
    {
        static Scanner instance;
        return instance;
    }

private:
    Scanner() : lineNr_(FIRST_LINE_NR), sourceCodeManager_(nullptr)
    {}

    Scanner (Scanner const&) = delete;
    void operator=(Scanner const&) = delete;

    static const std::map<char, int> delimiters;
    unsigned int lineNr_;
    static const unsigned int MAX_IDENTIFIER_LENGTH = 1024;
    static const unsigned int FIRST_LINE_NR = 1;

    SourceManagerPtr sourceCodeManager_;

public:
    void setSourceManager(std::string filename)
    {
        sourceCodeManager_ = std::make_shared<SourceCodeManager> (filename);
    }
    std::string getToken ();

};

typedef std::shared_ptr<Scanner> ScannerPtr;

#endif //REDCODEINTERPRETER_SCANNER_HPP
