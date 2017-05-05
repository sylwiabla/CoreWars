#include <iostream>
#include "redcodeInterpreter/scanner/Scanner.hpp"
#include "redcodeInterpreter/scanner/sourceCodeManager/FilesystemSourceManager.hpp"

using namespace std;

int main() {

    ErrorLoggerPtr errorLogger = std::make_shared<ErrorLogger> ();
    TokenPtr token;
    FilesystemManagerPtr filesystemManager = std::make_shared<FilesystemSourceManager> ("/home/sylwia/ClionProjects/RedcodeInterpreter/test/test");
    ScannerPtr scanner = std::make_shared<Scanner> (std::static_pointer_cast<SourceCodeManager> (filesystemManager), errorLogger);
    while (!scanner->endReached())
    {
        token = scanner->getToken();
        if (token)
            std::cout << token->getName() << std::endl;
    }

    ErrorPtr error = errorLogger->getError();
    while (error)
    {
        std::cout << "Line: " << std::get<0> (*error) << ", " << std::get<1> (*error) << std::endl;
        error = errorLogger->getError();
    }

    return 0;
}