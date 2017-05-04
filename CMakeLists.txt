cmake_minimum_required(VERSION 3.5)
project(RedcodeInterpreter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost COMPONENTS system filesystem thread REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

endif()

set(SCANNER src/redcodeInterpreter/scanner/Scanner.hpp src/redcodeInterpreter/scanner/Scanner.cpp)
set(SOURCE_FILES src/main.cpp src/redcodeInterpreter/parser/Parser.hpp src/redcodeInterpreter/parser/Parser.cpp)
set(SOURCE_CODE_MANAGER src/redcodeInterpreter/scanner/sourceCodeManager/SourceCodeManager.hpp src/redcodeInterpreter/scanner/sourceCodeManager/SourceCodeManager.cpp)
set(SOURCE_CODE_MANAGER_EXCEP src/redcodeInterpreter/scanner/sourceCodeManager/exceptions/SourceFileNotFound.hpp src/redcodeInterpreter/scanner/sourceCodeManager/exceptions/SourceFileNotFound.cpp)
set(ERROR_LOGGER src/redcodeInterpreter/errorLogger/ErrorLogger.hpp src/redcodeInterpreter/errorLogger/ErrorLogger.cpp)
set(TOKEN src/redcodeInterpreter/token/Token.hpp src/redcodeInterpreter/token/Token.cpp)
set(KEYWORD src/redcodeInterpreter/symbol/Symbol.hpp src/redcodeInterpreter/symbol/Modifier.hpp src/redcodeInterpreter/symbol/AddressingMode.hpp src/redcodeInterpreter/symbol/PseudoInstruction.hpp)
set(INSTRUCTION src/redcodeInterpreter/symbol/instruction/Instruction.hpp src/redcodeInterpreter/symbol/instruction/TwoArgsInstruction.hpp src/redcodeInterpreter/symbol/instruction/OneArgsInstruction.hpp src/redcodeInterpreter/symbol/instruction/ZeroArgsInstruction.hpp)
set(IDENTIFIER src/redcodeInterpreter/symbol/identifier/Label.hpp src/redcodeInterpreter/symbol/identifier/NumericValue.hpp src/redcodeInterpreter/symbol/identifier/Identifier.hpp)
set(INTERPRETER src/redcodeInterpreter/RedcodeInterpreter.cpp src/redcodeInterpreter/RedcodeInterpreter.hpp)

add_executable(RedcodeInterpreter ${SOURCE_FILES} ${SOURCE_CODE_MANAGER} ${SOURCE_CODE_MANAGER_EXCEP} ${ERROR_LOGGER} ${SCANNER} ${INTERPRETER} ${ERROR_LOGGER} ${TOKEN} ${KEYWORD} ${INSTRUCTION} ${IDENTIFIER})

if(Boost_FOUND)

    target_link_libraries(RedcodeInterpreter ${Boost_LIBRARIES})

endif()