//
// Created by Sylwia Blach on 4/19/17.
//

#ifndef REDCODEINTERPRETER_SCANNER_HPP
#define REDCODEINTERPRETER_SCANNER_HPP

#include <map>
#include "state/State.hpp"
#include "sourceCodeManager/SourceCodeManager.hpp"

/*class Scanner;

bool Scanner::isDelimiter(const char & c);
void Scanner::startStateHandler();
void Scanner::omitComment();
void Scanner::omitWhiteSpaces();
void Scanner::createToken();
void Scanner::logError();
void Scanner::logEOF();*/

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
        currentState_ = std::make_shared<State> ();
        currentState_ = startState_;
        lineNr_ = FIRST_LINE_NR;
    }

    Scanner (Scanner const&) = delete;
    void operator=(Scanner const&) = delete;

    static const std::map<char, int> delimiters_;
    unsigned int lineNr_;
    static const unsigned int MAX_IDENTIFIER_LENGTH = 1024;
    static const unsigned int FIRST_LINE_NR = 1;
    static const char COMMENT_START = ';';

    SourceManagerPtr sourceCodeManager_;

public:
    const std::string getToken ();

    static bool isDelimiter(const char & c);
    static void startStateHandler();
    static void omitComment();
    static void omitWhiteSpaces();
    static void createToken();
    static void logError();
    static void logEOF();

private:
    const StatePtr startState_ = std::make_shared<State> (&startStateHandler);
    const StatePtr commentState_ = std::make_shared<State> (&omitComment);
    const StatePtr wspaceState_ = std::make_shared<State> (&omitWhiteSpaces);
    const StatePtr errorState_ = std::make_shared<State> (true, &logError);
    const StatePtr tokenState_ = std::make_shared<State> (true, &createToken);
    const StatePtr endState_ = std::make_shared<State> (true, &logEOF);

    StatePtr currentState_;

};

typedef std::shared_ptr<Scanner> ScannerPtr;

#endif //REDCODEINTERPRETER_SCANNER_HPP
