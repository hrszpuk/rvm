#include "headers/translator.h"


#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


Buffer* TranslateInstructions(char* instructions) {
    char* line = strtok(instructions, "\n");
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
        if (strcasecmp(instr, BytecodeMap[i]) == 0) {
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


void TranslateFile(const char* filename, const char* output_filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", filename);
        return;
    }

    fseek(file, 0, SEEK_END);
    const long file_size = ftell(file);
    rewind(file);

    char* file_contents = malloc(sizeof(char) * file_size + 1);
    fread(file_contents, sizeof(char), file_size, file);
    file_contents[file_size] = '\0';

    const Buffer* buffer = TranslateInstructions(file_contents);

    free(file_contents);
    fclose(file);
    file = fopen(output_filename, "w");

    for (int i = 0; i < buffer->count; i++) {
        const TranslationResult* result = GetBufferData(buffer, i);
        fwrite(result->bytecode, sizeof(char), result->length, file);
    }

    printf("Translation complete.\n");
}
