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

