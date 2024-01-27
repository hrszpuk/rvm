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

void* ExtractMin(Heap* heap) {
    if (heap->size == 0) {
        return NULL;
    }
    void* min = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    Heapify(heap, 0);
    return min;
}

void* PeekHeap(Heap* heap) {
    if (heap->size == 0) {
        return NULL;
    }
    return heap->data[0];
}

void Heapify(Heap* heap, int index) {
    if (index >= heap->size || index < 0) {
        return;
    }
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int smallest = index;
    if (left < heap->size && heap->data[left] < heap->data[smallest]) {
        smallest = left;
    }
    if (right < heap->size && heap->data[right] < heap->data[smallest]) {
        smallest = right;
    }
    if (smallest != index) {
        void* temp = heap->data[index];
        heap->data[index] = heap->data[smallest];
        heap->data[smallest] = temp;
        Heapify(heap, smallest);
    }
}

void HeapSort(Heap* heap);

