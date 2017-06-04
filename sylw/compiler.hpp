#ifndef COMPILER_H
#define COMPILER_H
#include <string>
#include "src/redcodeInterpreter/scanner/Scanner.hpp"
#include "src/redcodeInterpreter/scanner/sourceCodeManager/FilesystemSourceManager.hpp"
#include "src/redcodeInterpreter/parser/Parser.hpp"
std::string compile(std::string filepath);
#endif // COMPILER_H
