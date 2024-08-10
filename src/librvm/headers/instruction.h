//
// Created by remy on 07/08/24.
//

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    HALT    = 0x00,
    NOOP    = 0x01,
    MOV     = 0x02,
    LOAD    = 0x03,
    STORE   = 0x04,
    PUSH    = 0x05,
    POP     = 0x06,
    ADD     = 0x07,
    SUB     = 0x08,
    MUL     = 0x09,
    DIV     = 0x0A,
    CALL    = 0x0B,
    RET     = 0x0C,
    JMP     = 0x0D,
    ALLOC   = 0x0E,
    FREE    = 0x0F
} Opcode;

typedef struct {
    Opcode opcode;
    uint16_t type_word;
    uint8_t *operands[3];
} Instruction;

Instruction parse_instruction(uint8_t *, size_t);

#endif //INSTRUCTION_H
