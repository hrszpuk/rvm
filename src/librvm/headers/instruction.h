//
// Created by remy on 07/08/24.
//

#ifndef INSTRUCTION_H
#define INSTRUCTION_H


typedef enum {
    HALT = 0x00,
    MOV  = 0x01,
    LOAD = 0x02,
    STORE = 0x03,
    PUSH = 0x04,
    POP  = 0x05,
    ADD  = 0x06,
    SUB  = 0x07,
    MUL  = 0x08,
    DIV  = 0x09,
    CALL = 0x0A,
    RET  = 0x0B,
    JMP  = 0x0C,
    ALLOC = 0x0D,
    FREE = 0x0E
} Opcode;

#endif //INSTRUCTION_H
