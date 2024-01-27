#include "headers/translator.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

Buffer* TranslateInstructions(char* instructions) {
    Buffer* result = CreateBuffer(10);
    char* line = strtok(instructions, "\n");
    while (line != NULL) {
        Instruction parsed = ParseInstruction(line);
        AddBufferData(result, &parsed);
        line = strtok(NULL, "\n");
    }

    printf("Buffer:\n");
    for (int i = 0; i < result->count; i++) {
        Instruction* instruction = GetBufferData(result, i);
        printf("%d %s\n", instruction->opcode, instruction->arg);
    }
    return result;
}

Instruction ParseInstruction(char* instruction) {
    Instruction result;
    result.opcode = 1;
    result.arg = NULL;
    result.type = 0;

    char* token = strtok(instruction, " ");
    if (token == NULL) {
        return result;
    }

    bool success = false;
    for (int i = 0; i < BYTECODE_INSTRUCTION_COUNT; i++) {
        if (strcasecmp(token, BytecodeMap[i]) == 0) {
            result.opcode = i;
            success = true;
            break;
        }
    }
    printf("Found: %d (%d)\n", result.opcode, success);

    if (!success) {
        return result;
    }

    token = strtok(NULL, " ");
    if (token == NULL) {
        return result;
    }

    result.arg = token;
    printf("Result: %d %s\n", result.opcode, result.arg);

    result.type = 1;

    return result;
}
