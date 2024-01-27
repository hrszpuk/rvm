//
// Created by hrs on 27/01/24.
//

#ifndef DICTIONARY_H
#define DICTIONARY_H

// NOTE(hrs): Value may need to be a union of different types, or a void*, in the future.
typedef struct {
    char* key;
    char* value;
    struct DictEntry* next;

    int hash;
    int used;
} DictEntry;

DictEntry* CreateDictEntry(char* key, char* value);     // Create a new DictEntry.
void FreeDictEntry(DictEntry* entry);                   // Free a DictEntry.

// Dictionary is a hash table of DictEntry.
// Implemented using linked lists.
typedef struct {
    DictEntry* entries;
    int size;
    int capacity;
} Dictionary;

Dictionary* CreateDictionary(int capacity);                         // Create a new Dictionary.
void FreeDictionary(Dictionary* dict);                              // Free a Dictionary.
void DictionaryInsert(Dictionary* dict, char* key, char* value);    // Insert a new key-value pair into the Dictionary.
char* DictionaryGet(Dictionary* dict, char* key);                   // Get the value associated with a key.
void DictionaryRemove(Dictionary* dict, char* key);                 // Remove a key-value pair from the Dictionary.
char** DictionaryGetKeys(Dictionary* dict);                         // Get all the keys in the Dictionary.
char** DictionaryGetValues(Dictionary* dict);                       // Get all the values in the Dictionary.
void DictionaryPrint(Dictionary* dict);                             // Print the Dictionary.

#endif //DICTIONARY_H
