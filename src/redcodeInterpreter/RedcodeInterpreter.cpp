//
// Created by Sylwia Blach on 4/26/17.
//

#include "RedcodeInterpreter.hpp"

const std::unordered_map<std::string, RedcodeInterpreter::TokenType> RedcodeInterpreter::keywords_ = {{"#", immidiateMode}, {"$", directMode}, {"@", indirectMode}, {"A", AModifier}, {"B", BModifier},
                                                                                  {"AB", ABModifier}, {"BA", BAModifier}, {"F", FModifier}, {"X", XModifier}, {"I", IModifier},
                                                                                  {"equ", equ}, {"org", org}, {"end", end}, {"for", forType}, {"rof", rof}, {"pin", pin}, {"dat", dat},
                                                                                  {"mov", mov}, {"add", add}, {"sub", sub}, {"mul", mul}, {"div", div}, {"mod", mod}, {"jmz", jmz}, {"jmn", jmn},
                                                                                  {"djn", djn}, {"spl", spl}, {"cmp", cmp}, {"seq", seq}, {"sne", sne}, {"slt", slt}, {"ldp", ldp}, {"stp", stp},
                                                                                  {"jmp", jmp}, {"nop", nop}, {",", comma}};