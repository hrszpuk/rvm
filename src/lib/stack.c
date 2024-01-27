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
}
