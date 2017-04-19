#include <iostream>
#include "redcodeInterpreter/sourceCodeManager/SourceCodeManager.hpp"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    SourceCodeManager * manager = new SourceCodeManager("/home/sylwia/ClionProjects/RedcodeInterpreter/test/test");
    char c;
    while(!manager->endReached())
    {
        c = manager->getNext();
        if (!manager->endReached())
            std::cout << c << std::endl;
    }
    return 0;
};