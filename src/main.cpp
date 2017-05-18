#include <iostream>
#include "redcodeInterpreter/scanner/Scanner.hpp"
#include "redcodeInterpreter/scanner/sourceCodeManager/FilesystemSourceManager.hpp"

namespace std
{
    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}

int main()
{
    ErrorLoggerPtr errorLogger = std::make_shared<ErrorLogger> ();
    TokenPtr token;
    ScannerPtr scanner = std::make_unique<Scanner> (std::make_unique<FilesystemSourceManager> ("/home/sylwia/ClionProjects/RedcodeInterpreter/test/test"), errorLogger);
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