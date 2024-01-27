//
// Created by hrs on 27/01/24.
//

#include "headers/vm.h"

#include <stdio.h>
#include <stdlib.h>

VM* CreateVM(const int stackCapacity, const int bufferCapacity) {
    VM* vm = malloc(sizeof(VM));
    vm->stack = CreateStack(stackCapacity);
    vm->buffer = CreateBuffer(bufferCapacity);
    vm->ip = 0;
    vm->state = 0;
    vm->debug = 0;
    return vm;
}

void DestroyVM(VM* vm) {
    DestroyBuffer(vm->buffer);
    FreeStack(vm->stack);
    free(vm);
}



