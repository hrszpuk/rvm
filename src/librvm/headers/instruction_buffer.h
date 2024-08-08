//
// Created by remy on 08/08/24.
//

#ifndef INSTRUCTION_BUFFER_H
#define INSTRUCTION_BUFFER_H

#include <stddef.h>

#include "instruction.h"
#include "label_map.h"

typedef struct {
    Instruction *buffer;
    size_t length;
    size_t capacity;
} InstructionBuffer;

InstructionBuffer *buffer_init(size_t capacity);
void buffer_free(InstructionBuffer *buffer);
void buffer_load(InstructionBuffer *buffer, Instruction *instructions, size_t size);
void buffer_add(InstructionBuffer *buffer, Opcode, uint8_t, int8_t *);
void buffer_resize(InstructionBuffer *buffer, size_t new_capacity);

#endif //INSTRUCTION_BUFFER_H
