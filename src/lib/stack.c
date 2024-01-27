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

void FreeStack(Stack* stack) {
    free(stack->data);
    free(stack);
}

void PrintStack(Stack* stack) {
    printf("Stack dump:\n");
    for (int i = 0; i < stack->count; i++) {
        printf("%d: %p", i, stack->data[i]);
    }
    printf("Total stack size: %d (capacity %d)\n", stack->count, stack->capacity);
}

void GrowStack(Stack* stack) {
    stack->capacity *= stack->growthFactor;
    stack->data = realloc(stack->data, sizeof(void*) * stack->capacity);
}

void ClearStack(Stack* stack) {
    stack->count = 0;
}

}
