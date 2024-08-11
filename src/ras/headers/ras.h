#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <stdint.h>

#define BYTECODE_INSTRUCTION_COUNT 13

// Look up the assembly of a bytecode value: BytecodeMap[bytecode value]
extern const char* BytecodeMap[BYTECODE_INSTRUCTION_COUNT];

unsigned char assembly2bytecode_opcode(char*);
uint8_t *assembly2bytecode_line(char*);
uint8_t *assembly2bytecode_string(char*);


#endif //TRANSLATOR_H
