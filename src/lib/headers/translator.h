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
    int type;
} Instruction;

Instruction* CreateInstruction(const unsigned char opcode, const char* arg, const int type);
void DestroyInstruction(Instruction* instruction);

typedef struct {
    char* file_contents;
    Buffer* instructions;
} BytecodeTranslator;

BytecodeTranslator* CreateBytecodeTranslator(char* file_contents);
void DestroyBytecodeTranslator(BytecodeTranslator* translator);
Buffer* Translate(BytecodeTranslator* translator);

#endif //TRANSLATOR_H
