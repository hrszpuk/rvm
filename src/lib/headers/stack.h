//
// Created by hrs on 24/01/24.
//

#ifndef STACK_H
#define STACK_H

typedef struct {
    void** data;
    int capacity;
    int count;
    int growthFactor;     // Default to 2 (NOTE: growth rate is always 1 * growthFactor)
} Stack;

Stack* CreateStack();
void* PopStack();
void PushStack(Stack*);
void FreeStack(Stack*);

#endif //STACK_H
