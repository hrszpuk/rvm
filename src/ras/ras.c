#include "headers/ras.h"

#include <string.h>

const char* BytecodeMap[BYTECODE_INSTRUCTION_COUNT] = {
    "halt",
    "noop",
    "load",
    "store",
    "push",
    "pop",
    "add",
    "sub",
    "mul",
    "div",
    "alloc",
    "free",
};

unsigned char assembly2bytecode_opcode(char* instruction) {
    for (int i = 0; i < BYTECODE_INSTRUCTION_COUNT; i++) {
        if (strcmp(instruction, BytecodeMap[i]) == 0) {
            return (char) i;
        }
    }
    return 0; // If its invalid then tell the vm to halt
}

uint8_t *assembly2bytecode_line(char* line) {

}

uint8_t *assembly2bytecode_string(char* string) {

}