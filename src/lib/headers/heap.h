//
// Created by hrs on 27/01/24.
//

#ifndef HEAP_H
#define HEAP_H

typedef struct {
    void** data;
    int size;
    int capacity;
} Heap;

Heap* CreateHeap(int capacity);             // Creates a heap with the given capacity
void DestroyHeap(Heap* heap);               // Destroys the heap
void InsertHeap(Heap* heap, void* data);    // Inserts data into the heap
void RemoveHeap(Heap* heap, void* data);    // Removes data from the heap
void* ExtractMin(Heap* heap);               // Extracts the minimum value from the heap
void* PeekHeap(Heap* heap);                 // Returns the minimum value from the heap
void Heapify(Heap* heap, int index);        // Heapifies the heap from the given index
void HeapSort(Heap* heap);                  // Sorts the heap
void PrintHeap(Heap* heap);                 // Prints the heap

#endif //HEAP_H
