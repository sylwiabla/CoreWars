cmake_minimum_required(VERSION 3.5)
project(RedcodeInterpreter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost COMPONENTS system filesystem thread REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

endif()

set(SOURCE_FILES src/main.cpp src/redcodeInterpreter/parser/Parser.hpp src/redcodeInterpreter/parser/Parser.cpp)
set(SOURCE_CODE_MANAGER src/redcodeInterpreter/scanner/sourceCodeManager/SourceCodeManager.hpp src/redcodeInterpreter/scanner/sourceCodeManager/SourceCodeManager.cpp)
set(SOURCE_CODE_MANAGER_EXCEP src/redcodeInterpreter/scanner/sourceCodeManager/exceptions/SourceFileNotFound.hpp src/redcodeInterpreter/scanner/sourceCodeManager/exceptions/SourceFileNotFound.cpp)
set(SCANNER src/redcodeInterpreter/scanner/Scanner.hpp src/redcodeInterpreter/scanner/Scanner.cpp)

add_executable(RedcodeInterpreter ${SOURCE_FILES} ${SOURCE_CODE_MANAGER} ${SOURCE_CODE_MANAGER_EXCEP} ${SCANNER})

if(Boost_FOUND)

    target_link_libraries(RedcodeInterpreter ${Boost_LIBRARIES})

endif()