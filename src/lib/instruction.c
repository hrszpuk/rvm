//
// Created by hrs on 24/01/24.
//

#include "headers/instruction.h"

#include <string.h>

Opcode BytecodeToOpcode(const char* bytecode) {
    Opcode code = OPCODE_ERROR;
    for(int i = 0; i < OPCODE_ENUM_LENGTH; i++) {
        if (strcmp(OpcodeStringMap[i], bytecode) == 0) {
            code = i;
        }
    }
    return code;
}

