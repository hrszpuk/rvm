//
// Created by hrs on 27/01/24.
//

#include "headers/dictionary.h"

#include <stdlib.h>

DictEntry* CreateDictEntry(char* key, char* value) {
    DictEntry* entry = malloc(sizeof(DictEntry));
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
    entry->hash = 0;
    entry->used = 0;
    return entry;
}

// NOTE(hrs): This function does not free the key or value.
void FreeDictEntry(DictEntry* entry) {
    free(entry);
}


