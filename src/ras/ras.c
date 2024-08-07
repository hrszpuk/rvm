#include "headers/ras.h"

#include <string.h>

unsigned char assembly_to_bytecode(char* instruction) {
    for (int i = 0; i < BYTECODE_INSTRUCTION_COUNT; i++) {
        if (strcmp(instruction, BytecodeMap[i]) == 0) {
            return (char) i;
        }
    }
    return 0; // If its invalid then tell the vm to halt
}