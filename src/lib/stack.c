//
// Created by hrs on 24/01/24.
//

#include "headers/stack.h"

#include <stdio.h>
#include <stdlib.h>

Stack* CreateStack(int capacity) {
    Stack* stack = malloc(sizeof(Stack));
    stack->data = malloc(sizeof(void*) * capacity);
    stack->capacity = capacity;
    stack->count = 0;
    stack->growthFactor = 2;
    return stack;
}

void* PopStack(Stack* stack) {
    void* data = TopStack(stack);
    stack->count--;
    return data;
}

void PushStack(Stack* stack, void* data) {
    if (stack->count == stack->capacity) {
        GrowStack(stack);
    }
    stack->data[stack->count] = data;
    stack->count++;
}
}
