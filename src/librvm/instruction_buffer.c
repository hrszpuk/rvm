#include <instruction_buffer.h>
#include <stdio.h>
#include <stdlib.h>

InstructionBuffer *buffer_init(size_t capacity) {
    InstructionBuffer *buffer = malloc(sizeof(InstructionBuffer));
    buffer->capacity = capacity;
    buffer->buffer = malloc(sizeof(Instruction) * buffer->capacity);
    buffer->length = 0;

    if (buffer->buffer == NULL) {
        fprintf(stderr, "InstructionBuffer failed to initialise because malloc returned NULL");
        free(buffer);
        exit(1);
    }
    return buffer;
}

void buffer_free(InstructionBuffer *buffer) {
    if (buffer) {
        if (buffer->buffer) free(buffer->buffer);
        free(buffer);
    }
}

void buffer_add(InstructionBuffer *buffer, Opcode opcode, uint8_t type, int8_t *operands) {
    if (buffer == NULL || buffer->buffer == NULL) {
        fprintf(stderr, "buffer_add failed because InstructionBuffer, or internal buffer, is NULL");
        exit(1);
    }

    if (buffer->length+1 >= buffer->capacity) buffer_resize(buffer, buffer->capacity * 2);

    buffer->buffer[buffer->length] = (Instruction){opcode, type, operands};
    buffer->length++;
}

void buffer_resize(InstructionBuffer *buffer, size_t new_capacity) {
    buffer->capacity = new_capacity;
    buffer->buffer = realloc(buffer->buffer, sizeof(Instruction) * buffer->capacity);
    if (buffer->buffer == NULL) {
        fprintf(stderr, "failed to resize InstructionBuffer because realloc returned NULL");
        exit(1);
    }
}