#include "headers/instruction.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Instruction parse_instruction(uint8_t *bytes, size_t length) {
    if (length < 3) { // At least 1 byte for opcode and 2 bytes for type_word
        fprintf(stderr, "Not enough bytes to decode instruction");
        exit(1);
    }

    Instruction instr;
    instr.opcode = bytes[0];
    instr.type_word = (bytes[1] << 8) | bytes[2];

    for (int i = 0; i < 3; i++) {
        instr.operands[i] = NULL;
    }

    size_t offset = 3;  // Start after opcode and type_word

    // Decode operands based on type_word and available bytes
    for (int i = 0; i < 3 && offset < length; i++) {
        uint8_t type = (instr.type_word >> (i * 5 + 1)) & 0x03;
        uint8_t type_info = (instr.type_word >> (i * 5 + 3)) & 0x07;

        size_t operand_size = 0;

        // Determine operand size based on type and type_info
        if (type == 0x0) {  // Register
            operand_size = 1;
        } else if (type == 0x1) {  // Immediate
            operand_size = 1 << type_info;  // 1, 2, 4, or 8 bytes
        } else if (type == 0x2) {  // Extended
            if (type_info <= 0x2) {
                operand_size = 4;
            } else if (type_info <= 0x3) {
                operand_size = 8;
            } else if (type_info == 0x4) {
                operand_size = 4;
            }
        }

        if (offset + operand_size <= length) {
            instr.operands[i] = (uint8_t*)malloc(operand_size);
            if (instr.operands[i]) {
                memcpy(instr.operands[i], &bytes[offset], operand_size);
            }
            offset += operand_size;
        } else {
            break;  // Not enough bytes to decode further
        }
    }

    return instr;
}

