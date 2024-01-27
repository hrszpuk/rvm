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
    int i = 0;
    const int length = strlen(instructions);

    char* arg = NULL, *instr = malloc(sizeof(char));
    int instr_size = 1, arg_size = 1;
    char* buffer = instr;
    int* buffer_size = &instr_size;

    while (i < length) {
        char c = instructions[i];
        buffer[*buffer_size - 1] = c;
        buffer = realloc(buffer, sizeof(char) * ++*buffer_size);

        if (c == '\n' || c == '\0') {
            Instruction instruction = ConstructInstruction(instr, arg);
            AddBufferData(result, &instruction);
        } else if (c == ' ') {
            arg = malloc(sizeof(char));
            buffer = arg;
            buffer_size = &arg_size;
        }
        i++;
    }

    printf("Buffer:\n");
    for (int k = 0; k < result->count; k++) {
        Instruction* instruction = GetBufferData(result, k);
        printf("%d %s\n", instruction->opcode, instruction->arg);
    }
    return result;
}

// This function assumes that instruction is a single line of code.
// It will return an Instruction struct with the opcode, argument, and type.
Instruction ConstructInstruction(char* instr_literal, char* arg) {
    Instruction result;
    result.opcode = 1;
    result.arg = arg;
    result.type = 0;

    for (int i = 0; i < BYTECODE_INSTRUCTION_COUNT; i++) {
        if (strcmp(instr_literal, BytecodeMap[i]) == 0) {
            result.opcode = i;
            break;
        }
    }

    if (arg == NULL) {
        return result;
    }

    // TODO: this type parsing can be improved.
    if (isdigit(arg[0])) {
        result.type = 1;
    } else if (arg[0] == '\'') {
        result.type = 2;
    } else if (arg[0] == '"') {
        result.type = 3;
    } else {
        result.type = 4;
    }

    return result;
}
