//
// Created by hrs on 26/01/24.
//

#ifndef BUFFER_H
#define BUFFER_H

typedef struct {
    int count;
    int capacity;
    void** data;
} Buffer;

Buffer* CreateBuffer(const int capacity); // Create a new buffer with the specified capacity.
void DestroyBuffer(Buffer* buffer); // Destroy the buffer and free all memory associated with it.
void* GetBufferData(const Buffer* buffer, const int index); // Get the data at the specified index.
void SetBufferData(const Buffer* buffer, const int index, void* element); // Set the data at the specified index.
void AddBufferData(Buffer* buffer, void* element); // Add data to the end of the buffer.
void RemoveBufferData(const Buffer* buffer, const int index); // Remove data from the buffer at the specified index.
void RemoveAllBufferData(Buffer* buffer); // Remove all data from the buffer.
void ClearBufferData(Buffer* buffer); // Clear the buffer and free the memory associated with it's data.

#endif //BUFFER_H
