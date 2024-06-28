//
// Created by hrs on 26/01/24.
//

#include "headers/buffer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

InstructionBuffer* CreateBuffer(const int capacity) {
    InstructionBuffer* buffer = malloc(sizeof(InstructionBuffer));
    buffer->count = 0;
    buffer->capacity = capacity;
    buffer->instructions = malloc(sizeof(Instruction) * capacity);

    return buffer;
}

void DestroyBuffer(InstructionBuffer* buffer) {
    free(buffer->instructions);
    free(buffer);
}

Instruction GetBufferData(const InstructionBuffer* buffer, const int index) {
    if (index < 0 || index >= buffer->count) {
        return (Instruction){0, 0, {}};
    }

    return buffer->instructions[index];
}

void SetBufferData(const InstructionBuffer* buffer, const int index, Instruction element) {
    if (index < 0 || index >= buffer->count) {
        return;
    }

    buffer->instructions[index] = element;
}

void AddBufferData(InstructionBuffer* buffer, Instruction element) {
    if (buffer->count >= buffer->capacity) {
        buffer->capacity *= 2;
        buffer->instructions = realloc(buffer->instructions, sizeof(Instruction) * buffer->capacity);
    }

    buffer->instructions[buffer->count] = element;
    buffer->count++;
}

void RemoveBufferData(const InstructionBuffer* buffer, const int index) {
    if (index < 0 || index >= buffer->count) {
        return;
    }

    for (int i = index; i < buffer->count - 1; i++) {
        buffer->instructions[i] = buffer->instructions[i + 1];
    }
}

void ClearBufferData(InstructionBuffer* buffer) {
    buffer->count = 0;
}
