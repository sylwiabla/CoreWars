//
// Created by sylwia on 4/19/17.
//

#ifndef REDCODEINTERPRETER_SCANNER_HPP
#define REDCODEINTERPRETER_SCANNER_HPP

#include <map>
#include "state/State.hpp"
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
    Scanner() : lineNr_(FIRST_LINE_NR), sourceCodeManager_(nullptr), currentState_(Scanner::startState_)
    {}

    Scanner (Scanner const&) = delete;
    void operator=(Scanner const&) = delete;

    static const std::map<char, int> delimiters_;
    unsigned int lineNr_;
    static const unsigned int MAX_IDENTIFIER_LENGTH = 1024;
    static const unsigned int FIRST_LINE_NR = 1;
    static const char COMMENT_START = ';';

    SourceManagerPtr sourceCodeManager_;

public:
    void setSourceManager(std::string filename)
    {
        sourceCodeManager_ = std::make_shared<SourceCodeManager> (filename);
    }
    const std::string & getToken ();

private:
    bool isDelimiter(const char & c);
    void startStateHandler();
    void omitComment();
    void omitWhiteSpaces();
    void createToken();
    void logError();
    void logEOF();

    static const StatePtr startState_ = std::make_shared(new State (startStateHandler));
    static const StatePtr commentState_ = std::make_shared(new State (omitComment));
    static const StatePtr wspaceState_ = std::make_shared(new State (omitWhiteSpaces));
    static const StatePtr errorState_ = std::make_shared(new State (true, logError));
    static const StatePtr tokenState_ = std::make_shared(new State (true, createToken));
    static const StatePtr endState_ = std::make_shared(new State (true, logEOF));

    StatePtr currentState_;

};

typedef std::shared_ptr<Scanner> ScannerPtr;

#endif //REDCODEINTERPRETER_SCANNER_HPP
