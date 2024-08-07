//
// Created by hrs on 26/01/24.
//

#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#define BYTECODE_INSTRUCTION_COUNT 13

// Look up the assembly of a bytecode value: BytecodeMap[bytecode value]
extern const char* BytecodeMap[BYTECODE_INSTRUCTION_COUNT] = {
    "halt",
    "noop",
    "load",
    "store",
    "push",
    "pop",
    "add",
    "sub",
    "mul",
    "div",
    "alloc",
    "free",
    "print"
};

unsigned char assembly_to_bytecode(char*);


#endif //TRANSLATOR_H
