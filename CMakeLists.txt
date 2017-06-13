cmake_minimum_required(VERSION 3.5)
project(RedcodeInterpreter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -std=c++1y -DCMAKE_CXX_COMPILER=/usr/bin/g++")

find_package(Boost COMPONENTS system filesystem thread unit_test_framework REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

endif()

add_definitions (-DBOOST_TEST_DYN_LINK)

set(SCANNER src/redcodeInterpreter/scanner/Scanner.hpp
        src/redcodeInterpreter/scanner/Scanner.cpp)
set(SOURCE_CODE_MANAGER src/redcodeInterpreter/scanner/sourceCodeManager/SourceCodeManager.hpp
        src/redcodeInterpreter/scanner/sourceCodeManager/FilesystemSourceManager.hpp
        src/redcodeInterpreter/scanner/sourceCodeManager/FilesystemSourceManager.cpp)
set(SOURCE_CODE_MANAGER_EXCEP src/redcodeInterpreter/scanner/sourceCodeManager/exceptions/SourceFileNotFound.hpp)
set(ERROR_LOGGER src/redcodeInterpreter/errorLogger/ErrorLogger.hpp
        src/redcodeInterpreter/errorLogger/ErrorLogger.cpp)
set(TOKEN src/redcodeInterpreter/scanner/token/Token.hpp)
set(INSTRUCTION src/redcodeInterpreter/instruction/Instruction.hpp)
set(IDENTIFIER src/redcodeInterpreter/symbolTableManager/identifier/Label.hpp
        src/redcodeInterpreter/symbolTableManager/identifier/Identifier.hpp
        src/redcodeInterpreter/symbolTableManager/SymbolTableManager.hpp
        src/redcodeInterpreter/symbolTableManager/identifier/Function.hpp)
set(PARSER src/redcodeInterpreter/parser/Parser.hpp
        src/redcodeInterpreter/parser/Parser.cpp
        src/redcodeInterpreter/instruction/CompositeInstruction.hpp
        src/redcodeInterpreter/instruction/SingleInstruction.hpp
        src/redcodeInterpreter/instruction/CompositeInstruction.cpp)
set(EMULATOR src/redcodeInterpreter/emulator/Emulator.hpp
        src/redcodeInterpreter/emulator/Emulator.cpp
        src/redcodeInterpreter/emulator/exceptions/OutOfMemory.hpp
        src/redcodeInterpreter/emulator/Warrior.hpp)
set(MAIN src/main.cpp)

set(TEST_SYMBOL_MANAGER test/redcodeInterpreter/symbolTableManager/SymbolTableManager.cpp
        test/redcodeInterpreter/scanner/Scanner.cpp)

set(TEST_SOURCE_MANAGER test/redcodeInterpreter/scanner/SourceCodeManager.cpp test/redcodeInterpreter/emulator/Emulator.cpp)

add_executable(RedcodeInterpreter ${PARSER} ${SOURCE_CODE_MANAGER} ${SOURCE_CODE_MANAGER_EXCEP} ${ERROR_LOGGER} ${SCANNER} ${TOKEN}
        ${KEYWORD} ${INSTRUCTION} ${IDENTIFIER} ${EMULATOR} ${MAIN})

add_executable (corewars_test ${TEST_SOURCE_MANAGER} ${TEST_SYMBOL_MANAGER} ${PARSER} ${SOURCE_CODE_MANAGER} ${SOURCE_CODE_MANAGER_EXCEP} ${ERROR_LOGGER} ${SCANNER} ${TOKEN}
        ${KEYWORD} ${INSTRUCTION} ${IDENTIFIER} ${EMULATOR})

if(Boost_FOUND)

    target_link_libraries(RedcodeInterpreter ${Boost_LIBRARIES})
    target_link_libraries (corewars_test ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

endif()