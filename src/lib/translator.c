#include "headers/translator.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** split(char* str, char c);

// NOTE(hrs): arg data is copied into the instruction, so it can be freed after the instruction is created.
Instruction* CreateInstruction(const unsigned char opcode, const char* arg, const int type) {
    Instruction* instruction = malloc(sizeof(Instruction));
    instruction->opcode = opcode;
    instruction->arg = NULL;
    if (arg != NULL) {
        instruction->arg = malloc(sizeof(char) * strlen(arg));
        strcpy(instruction->arg, arg);
    }
    instruction->type = type;
    return instruction;
}

void DestroyInstruction(Instruction* instruction) {
    free(instruction->arg);
    free(instruction);
}

BytecodeTranslator* CreateBytecodeTranslator(char* file_contents) {
    BytecodeTranslator* translator = malloc(sizeof(BytecodeTranslator));
    translator->file_contents = file_contents;
    translator->instructions = CreateBuffer(10);
    return translator;
}

void DestroyBytecodeTranslator(BytecodeTranslator* translator) {
    free(translator->file_contents);
    DestroyBuffer(translator->instructions);
    free(translator);
}

Buffer* Translate(BytecodeTranslator* translator) {
    char* file_contents = translator->file_contents;
    Buffer* instructions = translator->instructions;

    int instruction_count = 0;
    int line_size = 1;
    char* line = malloc(sizeof(char) * line_size);

    int i = 0;
    const int length = strlen(file_contents);
    while (i < length) {
        line[line_size - 1] = file_contents[i];
        line_size++;
        line = realloc(line, sizeof(char) * line_size);
        line[line_size - 1] = '\0';

        if (file_contents[i] == '\n') {
            // Remove new line character
            line[line_size - 2] = '\0';
            line_size--;
            line = realloc(line, sizeof(char) * line_size);

            printf("line: \"%s\"\n", line);

            // Split line into tokens
            char** tokens = split(line, ' ');
            int token_count = 0;

            while (tokens[token_count] != NULL) {
                printf("\"%s\"\n", tokens[token_count]);
                token_count++;
            }

            printf("Token count: %d\n", token_count);

            switch (token_count) {
                case 0: {
                    // Empty line
                    break;
                }
                case 1: {
                    // Instruction with no arguments
                    for (int j = 0; j < BYTECODE_INSTRUCTION_COUNT; j++) {
                        if (strcasecmp(tokens[0], BytecodeMap[j]) == 0) {
                            AddBufferData(instructions, CreateInstruction(j, NULL, 0));
                            instruction_count++;
                            break;
                        }
                    }
                    break;
                }
                case 2: {
                    // Instruction with one argument
                    for (int j = 0; j < BYTECODE_INSTRUCTION_COUNT; j++) {
                        if (strcasecmp(tokens[0], BytecodeMap[j]) == 0) {
                            AddBufferData(instructions, CreateInstruction(j, tokens[1], 1));
                            instruction_count++;
                            break;
                        }
                    }
                    break;
                }
                default: {
                    printf("Parse error: too many tokens on line %d\n", instruction_count);
                }
            }
            free(line);
            line_size = 1;
            line = malloc(sizeof(char) * line_size);
        }
        i++;
    }

    if (line_size > 1) {
        printf("Parse error: line %d is not terminated with a new line character\n", instruction_count);
    }

    printf("Found %d instructions:\n", instructions->count);
    for (int i = 0; i < instructions->count; i++) {
        Instruction* instruction = GetBufferData(instructions, i);
        if (instruction->arg == NULL) {
            printf("%d (%d): %s\n", i, instruction->opcode, BytecodeMap[instruction->opcode]);
        } else {
            printf("%d (%d): %s %s\n", i, instruction->opcode, BytecodeMap[instruction->opcode], instruction->arg);
        }
    }

    return instructions;
}


char** split(char* str, char delim) {
    int count = 0;
    char* temp = str;
    while (*temp) {
        if (*temp == delim) {
            count++;
        }
        temp++;
    }
    count += 2; // One extra for the last element and one for the NULL pointer

    char** result = malloc(sizeof(char *) * count);
    if (result == NULL) {
        return NULL;
    }

    char* token = strtok(str, &delim);
    int i = 0;
    while (token != NULL) {
        result[i++] = token;
        token = strtok(NULL, &delim);
    }
    result[i] = NULL; // Last element is the NULL pointer

    return result;
}

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
            Instruction instruction;
            instruction.opcode = 1;
            instruction.arg = arg;
            instruction.type = 0;

            for (int k = 0; k < BYTECODE_INSTRUCTION_COUNT; k++) {
                if (strcmp(instr, BytecodeMap[k]) == 0) {
                    instruction.opcode = k;
                    break;
                }
            }

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
