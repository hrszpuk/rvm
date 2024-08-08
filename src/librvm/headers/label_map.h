//
// Created by remy on 08/08/24.
//

#ifndef LABEL_MAP_H
#define LABEL_MAP_H

#include <stdint.h>

typedef struct {
    char *label;
    uint32_t *address;
} Label;

typedef struct {
    Label *labels;
    size_t size;
    size_t capacity;
} LabelMap;

#endif //LABEL_MAP_H
