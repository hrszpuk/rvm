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
    Instruction current;
    size_t size;
    LabelMap labels;
} InstructionBuffer;

InstructionBuffer buffer_init();
void buffer_free(InstructionBuffer *buffer);
void buffer_load(Instruction *instructions, size_t size);
void buffer_add(Instruction instruction);

#endif //INSTRUCTION_BUFFER_H
