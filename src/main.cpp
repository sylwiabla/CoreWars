#include <iostream>
#include "redcodeInterpreter/sourceCodeManager/SourceCodeManager.hpp"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    SourceCodeManager * manager = new SourceCodeManager("/home/sylwia/ClionProjects/RedcodeInterpreter/test/test");
    int c;
    while((c = manager->getNext()) != -1)
        std::cout << c << std::endl;
    return 0;
};