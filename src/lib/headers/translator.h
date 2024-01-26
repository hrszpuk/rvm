//
// Created by hrs on 26/01/24.
//

#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#define BYTECODE_INSTRUCTION_COUNT 40
#include "headers/buffer.h"


const char* BytecodeMap[BYTECODE_INSTRUCTION_COUNT] = {
    // Misc
    "halt",
    "noop",

    // Data operations
    "load",
    "store",
    "vload",
    "vstore",

    // Stack operations
    "push",
    "pop",
    "dup",
    "swap",

    // Arithmetic operations
    "add",
    "sub",
    "div",
    "mul",
    "mod",
    "inc",
    "dec",

    // Comparison operations
    "eq",
    "ne",
    "lt",
    "gt",
    "le",
    "ge",

    // Logical operations
    "land",
    "lor",
    "lnot",

    // Bitwise operations
    "and",
    "or",
    "xor",
    "not",
    "shl",
    "shr",

    // Control flow operations
    // NOTE: labels are defined as "<name>:" in the source code. The translator will convert these to numbers.
    "jmp",
    "jmpc",

    // Function operations
    "call",
    "ret",
    "begin",
    "end",

    // I/O operations
    "in",
    "out",
};

typedef struct { char* bytecode; int length; bool success; } TranslationResult;

#endif //TRANSLATOR_H
