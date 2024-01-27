//
// Created by hrs on 27/01/24.
//

#include "headers/dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    entry->next = (DictEntry*) CreateDictEntry(key, value);
    dict->size++;
}

char* DictionaryGet(Dictionary* dict, char* key) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash += key[i];
    }
    hash %= dict->capacity;

    DictEntry* entry = &dict->entries[hash];
    while (entry != NULL) {
        if (entry->key != NULL && strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = (DictEntry*) entry->next;
    }
    return NULL;
}

void DictionaryRemove(Dictionary* dict, char* key) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash += key[i];
    }
    hash %= dict->capacity;

    DictEntry* entry = &dict->entries[hash];
    while (entry->next != NULL) {
        if (entry->next->key != NULL && strcmp(entry->next->key, key) == 0) {
            DictEntry* next = (DictEntry*) entry->next->next;
            FreeDictEntry((DictEntry*) entry->next);
            entry->next = (DictEntry*) next;
            dict->size--;
            return;
        }
        entry = (DictEntry*) entry->next;
    }
}

void DictionaryPrint(Dictionary* dict) {
    printf("Dictionary dump:\n");
    for (int i = 0; i < dict->capacity; i++) {
        DictEntry* entry = (DictEntry*) dict->entries[i].next;
        while (entry != NULL) {
            printf("%s: %s\n", entry->key, entry->value);
            entry = (DictEntry*) entry->next;
        }
    }
}

// NOTE(hrs): return-value must be freed.
char** DictionaryGetKeys(Dictionary* dict) {
    char** keys = malloc(sizeof(char*) * dict->size);
    int index = 0;
    for (int i = 0; i < dict->capacity; i++) {
        DictEntry* entry = (DictEntry*) dict->entries[i].next;
        while (entry != NULL) {
            keys[index++] = entry->key;
            entry = (DictEntry*) entry->next;
        }
    }
    return keys;
}

// NOTE(hrs): return-value must be freed.
char** DictionaryGetValues(Dictionary* dict) {
    char** values = malloc(sizeof(char*) * dict->size);
    int index = 0;
    for (int i = 0; i < dict->capacity; i++) {
        DictEntry* entry = (DictEntry*) dict->entries[i].next;
        while (entry != NULL) {
            values[index++] = entry->value;
            entry = (DictEntry*) entry->next;
        }
    }
    return values;
}