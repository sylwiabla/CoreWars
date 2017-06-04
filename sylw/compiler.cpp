#include "compiler.hpp"

/*namespace std
{
    template<typename T, typename... Args>
    std::shared_ptr<T> make_unique(Args&&... args)
    {
        return std::shared_ptr<T>(new T(std::forward<Args>(args)...));
    }
}*/

std::string compile(std::string filepath){
    ErrorLoggerPtr errorLogger = std::make_shared<ErrorLogger> ();
    SymbolTablePtr symbolTableManager = std::make_shared<SymbolTableManager> ();
    //ParserPtr parser = std::make_shared<Parser> (errorLogger, std::make_unique<Scanner> (std::make_unique<FilesystemSourceManager>
                                                                                                // (filepath), errorLogger),symbolTableManager);
    std::string strError = "";
    //parser->parse();
    ErrorPtr error = errorLogger->getError();
    while (error)
    {
        strError = "Line: "+std::to_string(std::get<0> (*error))+ "* "+ std::get<1> (*error);
        error = errorLogger->getError();
    }
    return strError;
}
