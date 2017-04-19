//
// Created by sylwia on 4/19/17.
//

#ifndef REDCODEINTERPRETER_SCANNER_HPP
#define REDCODEINTERPRETER_SCANNER_HPP

class Scanner
{
public:
    static Scanner & getInstance()
    {
        static Scanner instance;
        return instance;
    }

private:
    Scanner()
    {}

    Scanner (Scanner const&) = delete;
    void operator=(Scanner const&) = delete;



};

#endif //REDCODEINTERPRETER_SCANNER_HPP
