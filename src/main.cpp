#include <iostream>
#include "redcodeInterpreter/scanner/Scanner.hpp"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    Scanner::getInstance().setSourceManager("/home/sylwia/ClionProjects/RedcodeInterpreter/test/test");

    return 0;
};