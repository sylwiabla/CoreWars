#include <iostream>
#include "redcodeInterpreter/scanner/Scanner.hpp"

using namespace std;

int main() {
    Scanner::getInstance();
    std::string temp = "";
    Scanner::getInstance().setSourceManager("/home/sylwia/ClionProjects/RedcodeInterpreter/test/test");

    do
    {
        temp = Scanner::getInstance().getToken();
        std::cout << temp << std::endl;
    }
    while((temp != "End of source file") && (temp != "Error: too long identifier name"));

    return 0;
}