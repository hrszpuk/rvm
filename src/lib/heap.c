//
// Created by hrs on 27/01/24.
//

#include "headers/heap.h"

Heap* CreateHeap(int capacity);

void DestroyHeap(Heap* heap);

void InsertHeap(Heap* heap, void* data);

void RemoveHeap(Heap* heap, void* data);

void* ExtractMin(Heap* heap);

void* PeekHeap(Heap* heap);

void Heapify(Heap* heap, int index);

void HeapSort(Heap* heap);

