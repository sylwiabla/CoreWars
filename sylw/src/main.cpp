#include <iostream>
#include <string>
#include "redcodeInterpreter/scanner/Scanner.hpp"
#include "redcodeInterpreter/scanner/sourceCodeManager/FilesystemSourceManager.hpp"
#include "redcodeInterpreter/parser/Parser.hpp"

/*namespace std
{
    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}*/


/*std::string compile(std::string filepath){
    ErrorLoggerPtr errorLogger = std::make_shared<ErrorLogger> ();
    SymbolTablePtr symbolTableManager = std::make_shared<SymbolTableManager> ();
    ParserPtr parser = std::make_shared<Parser> (errorLogger, std::make_unique<Scanner> (std::make_unique<FilesystemSourceManager> (filepath), errorLogger),symbolTableManager);
    std::string strError = "";
    parser->parse();
    ErrorPtr error = errorLogger->getError();
    while (error)
    {
        strError = "Line: "+std::to_string(std::get<0> (*error))+ "* "+ std::get<1> (*error);
        error = errorLogger->getError();
    }
    return strError;
}*/


int main()
{
    ErrorLoggerPtr errorLogger = std::make_shared<ErrorLogger> ();
    SymbolTablePtr symbolTableManager = std::make_shared<SymbolTableManager> ();
    //ParserPtr parser = std::make_shared<Parser> (errorLogger, std::make_shared<Scanner> (std::make_unique<FilesystemSourceManager>("/home/klis/STUDIA/6sem/ZPR/roboczy/sylw/test/test"), errorLogger),symbolTableManager);
    //parser->parse();
    ErrorPtr error = errorLogger->getError();
    while (error)
    {
        std::cout << "Line: " << std::get<0> (*error) << "* " << std::get<1> (*error) << std::endl;
        error = errorLogger->getError();
    }
    //compile("../test/test");
    return 0;
}

/*#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(Compiler)
{
    def("compile", compile);
}*/
