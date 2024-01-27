//
// Created by hrs on 26/01/24.
//

#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#define BYTECODE_INSTRUCTION_COUNT 40
#include "buffer.h"

extern const char* BytecodeMap[BYTECODE_INSTRUCTION_COUNT];
typedef struct { char* bytecode; int length; bool success; } TranslationResult;

Buffer* TranslateInstructions(char* instructions);
TranslationResult TranslateInstruction(char* instruction);
void TranslateFile(const char* filename, const char* outputFilename);

#endif //TRANSLATOR_H
