#ifndef COMPILER_H
#define COMPILER_H
#include <string>
#include "redcodeInterpreter/scanner/Scanner.hpp"
#include "redcodeInterpreter/scanner/sourceCodeManager/FilesystemSourceManager.hpp"
#include "redcodeInterpreter/parser/Parser.hpp"
std::string compile(char* filepath);
#endif // COMPILER_H
