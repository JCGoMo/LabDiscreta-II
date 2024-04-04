// Simple hash table implemented in C.

#ifndef _HT_H
#define _HT_H

#include <stdbool.h>
#include "u32.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

// Hash table structure: create with ht_create, free with ht_destroy.
typedef struct ht *hash;

// Create hash table and return pointer to it, or NULL if out of memory.
hash ht_create(void);

// Free memory allocated for hash table, including allocated keys.
void ht_destroy(hash table);

// Get item with given key (NUL-terminated) from hash table. Return
// value (which was set with ht_set), or NULL if key not found.
void* ht_get(hash table, const char* key);

// Set item with given key (NUL-terminated) to value (which must not
// be NULL). If not already present in table, key is copied to newly
// allocated memory (keys are freed automatically when ht_destroy is
// called). Return address of copied key, or NULL if out of memory.
const char* ht_set(hash table, const char* key, void* value);

// Return number of items in hash table.
size_t ht_length(hash table);

// Hash table iterator: create with ht_iterator, iterate with ht_next.
typedef struct {
    const char* key;  // current key
    void* value;      // current value

    // Don't use these fields directly.
    hash _table;       // reference to hash table being iterated
    size_t _index;    // current index into ht._entries
} hti;

#endif // _HT_H