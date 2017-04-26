cmake_minimum_required(VERSION 3.5)
project(RedcodeInterpreter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost COMPONENTS system filesystem thread REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

endif()

set(INTERPRETER src/redcodeInterpreter/RedcodeInterpreter.hpp)
set(SOURCE_FILES src/main.cpp src/redcodeInterpreter/parser/Parser.hpp src/redcodeInterpreter/parser/Parser.cpp)
set(SOURCE_CODE_MANAGER src/redcodeInterpreter/scanner/sourceCodeManager/SourceCodeManager.hpp src/redcodeInterpreter/scanner/sourceCodeManager/SourceCodeManager.cpp)
set(SOURCE_CODE_MANAGER_EXCEP src/redcodeInterpreter/scanner/sourceCodeManager/exceptions/SourceFileNotFound.hpp src/redcodeInterpreter/scanner/sourceCodeManager/exceptions/SourceFileNotFound.cpp)
set(SCANNER src/redcodeInterpreter/scanner/Scanner.hpp src/redcodeInterpreter/scanner/Scanner.cpp)
set(ERROR_LOGGER src/redcodeInterpreter/errorLogger/ErrorLogger.hpp src/redcodeInterpreter/errorLogger/ErrorLogger.cpp)
set(TOKEN src/redcodeInterpreter/token/Token.hpp src/redcodeInterpreter/token/Token.cpp src/redcodeInterpreter/token/keyword/identifier/Identifier.hpp)
set(KEYWORD src/redcodeInterpreter/token/keyword/Keyword.hpp src/redcodeInterpreter/token/keyword/Modifier.hpp src/redcodeInterpreter/token/keyword/AddressingMode.hpp src/redcodeInterpreter/token/keyword/PseudoInstruction.hpp)
set(INSTRUCTION src/redcodeInterpreter/token/keyword/instruction/Instruction.hpp src/redcodeInterpreter/token/keyword/instruction/TwoArgsInstruction.hpp src/redcodeInterpreter/token/keyword/instruction/OneArgsInstruction.hpp src/redcodeInterpreter/token/keyword/instruction/ZeroArgsInstruction.hpp)
set(IDENTIFIER src/redcodeInterpreter/token/keyword/identifier/Label.hpp src/redcodeInterpreter/token/keyword/identifier/NumericValue.hpp)
set(INTERPRETER src/redcodeInterpreter/RedcodeInterpreter.cpp)

add_executable(RedcodeInterpreter ${SOURCE_FILES} ${SOURCE_CODE_MANAGER} ${SOURCE_CODE_MANAGER_EXCEP} ${SCANNER} ${ERROR_LOGGER} ${TOKEN} ${KEYWORD} ${INSTRUCTION} ${INTERPRETER} ${IDENTIFIER}
        ${INTERPRETER})

if(Boost_FOUND)

    target_link_libraries(RedcodeInterpreter ${Boost_LIBRARIES})

endif()