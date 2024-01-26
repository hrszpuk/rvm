#include "headers/translator.h"


#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


Buffer* TranslateInstructions(char* instructions) {
    const char* line = strtok(instructions, "\n");
    Buffer* instr_buffer = CreateBuffer(1);

    while (line != NULL) {
        if (isalpha(line[0])) {
            TranslationResult result = TranslateInstruction(line);
            AddBufferData(instr_buffer, &result);
        }

        line = strtok(NULL, "\n");
    }

    return instr_buffer;
}


// NOTE: instructions are in the form "<instruction> <arg>". Addional arguments are stored on the stack.
// i.e. "push 5" will push 5 onto the stack, "add" will add the top two values on the stack.
// Return format: first character is the opcode, the rest are the arguments, if any. End with a \n terminator.
TranslationResult TranslateInstruction(char* instruction) {
    const char* instr = strtok(instruction, " ");
    unsigned char opcode = 0;
    char* args = malloc(sizeof(char) * 1);
    int args_size = 1;

    bool success = false;

    for (int i = 0; i < BYTECODE_INSTRUCTION_COUNT; i++) {
        if (strcmp(instr, BytecodeMap[i]) == 0) {
            opcode = i;
            success = true;
            break;
        }
    }

    instr = strtok(NULL, " ");
    while (instr != NULL) {
        args_size++;
        args = realloc(args, sizeof(char) * args_size);
        args[args_size - 1] = atoi(instr);
        instr = strtok(NULL, " ");
    }

    args_size++;
    args = realloc(args, sizeof(char) * args_size);
    args[args_size - 1] = '\n';

    char* result = malloc(sizeof(char) * args_size + 1);
    result[0] = opcode;

    memcpy(result + 1, args, args_size);
    free(args);

    return (TranslationResult) { result, args_size + 1, success };
}
