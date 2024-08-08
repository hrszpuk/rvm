#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#define BYTECODE_INSTRUCTION_COUNT 13

// Look up the assembly of a bytecode value: BytecodeMap[bytecode value]
extern const char* BytecodeMap[BYTECODE_INSTRUCTION_COUNT];

unsigned char assembly_to_bytecode(char*);


#endif //TRANSLATOR_H
