//
// Created by hrs on 01/07/24.
//
#include <stdlib.h>
#include <string.h>
#include "headers/directive.h"

DirectiveBuffer* create_directive_buffer(int capacity) {
    DirectiveBuffer* df = malloc(sizeof(DirectiveBuffer));
    df->directives = malloc(sizeof(Directive) * capacity);
    df->count = 0;
    df->capacity = capacity;
    return df;
}

void destroy_directive_buffer(DirectiveBuffer* df) {
    if (df) {
        free(df->directives);
        free(df);
    }
}

Directive get_directive(DirectiveBuffer* df) {

}

void add_directive(DirectiveBuffer* df) {

}