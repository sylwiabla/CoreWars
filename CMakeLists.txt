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
set(KEYWORD src/redcodeInterpreter/mnemonic/Mnemonic.hpp src/redcodeInterpreter/mnemonic/Modifier.hpp src/redcodeInterpreter/mnemonic/AddressingMode.hpp src/redcodeInterpreter/mnemonic/PseudoInstruction.hpp)
set(INSTRUCTION src/redcodeInterpreter/mnemonic/instruction/Instruction.hpp src/redcodeInterpreter/mnemonic/instruction/TwoArgsInstruction.hpp src/redcodeInterpreter/mnemonic/instruction/OneArgsInstruction.hpp src/redcodeInterpreter/mnemonic/instruction/ZeroArgsInstruction.hpp)
set(IDENTIFIER src/redcodeInterpreter/mnemonic/identifier/Label.hpp src/redcodeInterpreter/mnemonic/identifier/NumericValue.hpp src/redcodeInterpreter/mnemonic/identifier/Identifier.hpp)
set(INTERPRETER src/redcodeInterpreter/RedcodeInterpreter.cpp src/redcodeInterpreter/RedcodeInterpreter.hpp)

add_executable(RedcodeInterpreter ${SOURCE_FILES} ${SOURCE_CODE_MANAGER} ${SOURCE_CODE_MANAGER_EXCEP} ${ERROR_LOGGER} ${SCANNER} ${INTERPRETER} ${ERROR_LOGGER} ${TOKEN} ${KEYWORD} ${INSTRUCTION} ${IDENTIFIER})

if(Boost_FOUND)

    target_link_libraries(RedcodeInterpreter ${Boost_LIBRARIES})

endif()