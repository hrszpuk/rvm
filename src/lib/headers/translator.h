//
// Created by hrs on 26/01/24.
//

#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#define BYTECODE_INSTRUCTION_COUNT 40
#include "buffer.h"

// BytecodeMap is a map of all human readable bytecode strings to their opcode values (single byte instructions).
extern const char* BytecodeMap[BYTECODE_INSTRUCTION_COUNT]; // see translator.c

typedef struct {
    unsigned char opcode;
    char* arg;
    int type; // 0 = no arg, 1 = int, 2 = char, 3 = string, 4 = label
} Instruction;

// TranslateInstructions takes a string of human readable instructions and returns a buffer of Instruction data.
// The last value of the buffer is a NULL pointer.
Buffer* TranslateInstructions(char*);
Instruction ConstructInstruction(char*, char*);


#endif //TRANSLATOR_H
