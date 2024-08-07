//
// Created by hrs on 27/01/24.
//

#include "headers/vm.h"

#include <stdio.h>
#include <stdlib.h>

VM *init_vm(size_t memory_size, size_t stack_size, size_t heap_size) {
    VM *vm = malloc(sizeof vm);
    if (vm == NULL) {
        fprintf(stderr, "Failed to allocate memory for VM.\n");
        exit(1);
    }

    vm->memory = malloc(sizeof(char) * memory_size);
    if (vm->memory == NULL) {
        fprintf(stderr, "Failed to allocate memory for VM memory.\n");
        free(vm);
        exit(1);
    }



    return vm;
}


void free_vm(VM *vm) {

}


void load_program(VM *vm, uint8_t *program, size_t size) {

}


void run(VM *vm, const uint8_t *program, size_t program_size) {

}
