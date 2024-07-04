//
// Created by hrs on 26/01/24.
//

#include "headers/buffer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

InstructionBuffer* create_buffer(const int capacity) {
    InstructionBuffer* buffer = malloc(sizeof(InstructionBuffer));
    buffer->count = 0;
    buffer->capacity = capacity;
    buffer->instructions = malloc(sizeof(Instruction) * capacity);

    return buffer;
}

void destroy_buffer(InstructionBuffer* buffer) {
    free(buffer->instructions);
    free(buffer);
}

Instruction get_buffer_data(const InstructionBuffer* buffer, int index) {
    if (index < 0 || index >= buffer->count) {
        return (Instruction){0, 0, {}};
    }

    return buffer->instructions[index];
}

void set_buffer_data(const InstructionBuffer* buffer, int index, Instruction element) {
    if (index < 0 || index >= buffer->count) {
        return;
    }

    buffer->instructions[index] = element;
}

void add_buffer_data(InstructionBuffer* buffer, Instruction element) {
    if (buffer->count >= buffer->capacity) {
        buffer->capacity *= 2;
        buffer->instructions = realloc(buffer->instructions, sizeof(Instruction) * buffer->capacity);
    }

    buffer->instructions[buffer->count] = element;
    buffer->count++;
}

void remove_buffer_data(const InstructionBuffer* buffer, int index) {
    if (index < 0 || index >= buffer->count) {
        return;
    }

    for (int i = index; i < buffer->count - 1; i++) {
        buffer->instructions[i] = buffer->instructions[i + 1];
    }
}

void clear_buffer_data(InstructionBuffer* buffer) {
    buffer->count = 0;
}
