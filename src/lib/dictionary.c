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

Dictionary* CreateDictionary(int capacity) {
    Dictionary* dict = malloc(sizeof(Dictionary));
    dict->entries = malloc(sizeof(DictEntry) * capacity);
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

// Free the Dictionary and all its entries.
void FreeDictionary(Dictionary* dict) {
    for (int i = 0; i < dict->capacity; i++) {
        DictEntry* entry = (DictEntry*) dict->entries[i].next;
        while (entry != NULL) {
            DictEntry* next = (DictEntry*) entry->next;
            FreeDictEntry(entry);
            entry = next;
        }
    }
    free(dict->entries);
    free(dict);
}

void DictionaryInsert(Dictionary* dict, char* key, char* value) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash += key[i];
    }
    hash %= dict->capacity;

    DictEntry* entry = &dict->entries[hash];
    while (entry->next != NULL) {
        entry = (DictEntry*) entry->next;
    }
    entry->next = (struct DictEntry*) CreateDictEntry(key, value);
    dict->size++;
}

