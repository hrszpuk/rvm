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
