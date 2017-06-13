#include <iostream>
#include "redcodeInterpreter/scanner/Scanner.hpp"
#include "redcodeInterpreter/scanner/sourceCodeManager/FilesystemSourceManager.hpp"
#include "redcodeInterpreter/parser/Parser.hpp"
#include "redcodeInterpreter/emulator/Emulator.hpp"
#include "redcodeInterpreter/emulator/exceptions/OutOfMemory.hpp"

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
    SymbolTablePtr symbolTableManager = std::make_shared<SymbolTableManager> ();
    ParserPtr parser = std::make_shared<Parser> (errorLogger, std::make_unique<Scanner> (std::make_unique<FilesystemSourceManager>
                                                                                                 ("/home/sylwia/Documents/Projects/ClionProjects/RedcodeInterpreter/test/test"), errorLogger),
                                                 symbolTableManager);
    CodePtr code = parser->parse();

    ErrorPtr error = errorLogger->getError();
    if (error)
    {
        while (error)
        {
            std::cout << "Line: " << std::get<0> (*error) << "* " << std::get<1> (*error) << std::endl;
            error = errorLogger->getError();
        }
        return 0;
    }

    try {
        TwoArgsInstrPtr i = std::make_shared<TwoArgsInstruction> (TwoArgsInstruction ());
        Emulator * emulator = new Emulator((unsigned long) 300, (int) 40, i);
        emulator->loadWarriors(code, code);

        while (emulator->invokeInstruction() == Emulator::WAITING)
        {
            for (InstructionPtr instruction : emulator->getCore())
                std::cout << instruction->getType() << std::endl;
        }

        delete(emulator);
    } catch (const OutOfMemory & excep)
    {
        return 0;
    }



    return 0;
}