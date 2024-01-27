//
// Created by hrs on 27/01/24.
//

#include "headers/heap.h"

#include <stdlib.h>

Heap* CreateHeap(int capacity) {
    Heap* heap = malloc(sizeof(Heap) * capacity);
    heap->data = malloc(sizeof(void*) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void DestroyHeap(Heap* heap) {
    free(heap->data);
    free(heap);
}

void InsertHeap(Heap* heap, void* data) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = realloc(heap->data, sizeof(void*) * heap->capacity);
    }
    heap->data[heap->size] = data;
    heap->size++;
    Heapify(heap, heap->size - 1);
}

void RemoveHeap(Heap* heap, void* data) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->data[i] == data) {
            heap->data[i] = heap->data[heap->size - 1];
            heap->size--;
            Heapify(heap, i);
            return;
        }
    }
}

void* ExtractMin(Heap* heap);

void* PeekHeap(Heap* heap);

void Heapify(Heap* heap, int index);

void HeapSort(Heap* heap);

