//
// Created by hrs on 26/01/24.
//

#include "headers/buffer.h"

#include <stdlib.h>

Buffer* CreateBuffer(const int capacity) {
    Buffer* buffer = malloc(sizeof(Buffer));
    buffer->count = 0;
    buffer->capacity = capacity;
    buffer->data = malloc(sizeof(void*) * capacity);

    return buffer;
}

void DestroyBuffer(Buffer* buffer) {
    for (int i = 0; i < buffer->count; i++) {
        free(buffer->data[i]);
    }

    free(buffer);
}

void* GetBufferData(const Buffer* buffer, const int index) {
    if (index < 0 || index >= buffer->count) {
        return NULL;
    }

    return buffer->data[index];
}

void SetBufferData(const Buffer* buffer, const int index, void* element) {
    if (index < 0 || index >= buffer->count) {
        return;
    }

    buffer->data[index] = element;
}

void AddBufferData(Buffer* buffer, void* element) {
    if (buffer->count >= buffer->capacity) {
        buffer->capacity *= 2;
        buffer->data = realloc(buffer->data, sizeof(void*) * buffer->capacity);
    }

    buffer->data[buffer->count] = element;
    buffer->count++;
}
