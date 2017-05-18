cmake_minimum_required(VERSION 3.5)
project(RedcodeInterpreter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -std=c++1y -DCMAKE_CXX_COMPILER=/usr/bin/g++")

find_package(Boost COMPONENTS system filesystem thread REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

endif()

set(SCANNER src/redcodeInterpreter/scanner/Scanner.hpp
        src/redcodeInterpreter/scanner/Scanner.cpp)
set(SOURCE_CODE_MANAGER src/redcodeInterpreter/scanner/sourceCodeManager/SourceCodeManager.hpp
        src/redcodeInterpreter/scanner/sourceCodeManager/FilesystemSourceManager.hpp
        src/redcodeInterpreter/scanner/sourceCodeManager/FilesystemSourceManager.cpp)
set(SOURCE_CODE_MANAGER_EXCEP src/redcodeInterpreter/scanner/sourceCodeManager/exceptions/SourceFileNotFound.hpp)
set(ERROR_LOGGER src/redcodeInterpreter/errorLogger/ErrorLogger.hpp
        src/redcodeInterpreter/errorLogger/ErrorLogger.cpp)
set(TOKEN src/redcodeInterpreter/scanner/token/Token.hpp)
set(INSTRUCTION src/redcodeInterpreter/parser/instruction/Instruction.hpp)
set(IDENTIFIER src/redcodeInterpreter/symbolTableManager/identifier/Label.hpp
        src/redcodeInterpreter/symbolTableManager/identifier/Identifier.hpp
        src/redcodeInterpreter/symbolTableManager/SymbolTableManager.hpp
        src/redcodeInterpreter/symbolTableManager/identifier/Function.hpp)
set(SOURCE_FILES src/main.cpp
        src/redcodeInterpreter/parser/Parser.hpp
        src/redcodeInterpreter/parser/Parser.cpp
        src/redcodeInterpreter/parser/instruction/CompositeInstruction.hpp
        src/redcodeInterpreter/parser/instruction/SingleInstruction.hpp src/redcodeInterpreter/parser/instruction/CompositeInstruction.cpp)

add_executable(RedcodeInterpreter ${SOURCE_FILES} ${SOURCE_CODE_MANAGER} ${SOURCE_CODE_MANAGER_EXCEP} ${ERROR_LOGGER} ${SCANNER} ${TOKEN} ${KEYWORD} ${INSTRUCTION} ${IDENTIFIER})

if(Boost_FOUND)

    target_link_libraries(RedcodeInterpreter ${Boost_LIBRARIES})

endif()