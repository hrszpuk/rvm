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

LabelMap label_map_init(size_t capacity);
void label_map_free(LabelMap);

#endif //LABEL_MAP_H
