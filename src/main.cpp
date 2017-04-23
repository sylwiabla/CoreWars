#include <iostream>
#include "redcodeInterpreter/scanner/Scanner.hpp"

using namespace std;

int main() {
    std::string temp = "";
    Scanner::getInstance().setSourceManager("/home/sylwia/ClionProjects/RedcodeInterpreter/test/test");

    do
    {
        temp = Scanner::getInstance().getToken();
        std::cout << temp << std::endl;
    }
    while((temp != "Too long identifier") && (temp != "EOF"));

    return 0;
}