#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdint.h>
#include <stddef.h>

typedef struct hash_entry hash_entry;

typedef struct hash_table {
    unsigned int key_count;
    unsigned int array_size;
    hash_entry **array;
    unsigned int collisions;
    int flags;
} hash_table;

typedef struct ht_iterator {
    hash_table *table;
    hash_entry *entry;
    unsigned int index;
} hash_iterator;

// HT flags
#define HT_NONE 0
#define HT_KEY_CONST 1
#define HT_VALUE_CONST 2

//----------------------------------
// HashTable functions
//----------------------------------

// initializes the hash_table struct
void ht_init(hash_table *table, int flags);

// destroys the hash_table struct 
// and frees all relevant memory
void ht_destroy(hash_table *table);

// inserts the {key: value} pair into the hash table, 
// makes copies of both key and value
void ht_insert(hash_table *table, void *key, size_t key_size, void *value, size_t value_size);

// returns a pointer to the value with the matching key, 
// value_size is set to the size in bytes of the value
void* ht_get(hash_table *table, void *key, size_t key_size, size_t *value_size);

// removes the entry corresponding to the 
// specified key from the hash table
void ht_remove(hash_table *table, void *key, size_t key_size);

// returns 1 if the hash_table contains the entry 
// specified by key, 0 otherwise
int ht_contains(hash_table *table, void *key, size_t key_size);

// returns the number of valid entries 
// in the hash table
unsigned int ht_size(hash_table *table);

// returns an array of keys
// sets key_count to the length of the array
void** ht_keys(hash_table *table, unsigned int *key_count);

// removes all entries from the hash table
void ht_clear(hash_table *table);

// resizes the hash table's internal array
// and recomputes all of the keys
void ht_resize(hash_table *table, unsigned int new_size);

// sets the global security seed to be used in hash function
void ht_set_seed(uint32_t seed);

//----------------------------------
// Hashtable Iterator functions
//----------------------------------

// Initializes an iterator that can be used to iterate
// inside the hash table entries. The hash table *cannot* be changed
// during the iteration
void ht_it_init(hash_iterator *it, hash_table *table);

// Fetch a new entry. Returns 1 if there is an entry,
// 0 if we are on end of table.
int ht_it_next(hash_iterator *it);

// Fetch the key of the current entry. If size is not null,
// it will contain the size of the key
void *ht_it_get_key(hash_iterator *it, size_t *size);

// Fetch the value of the current entry. If size is not null,
// it will contain the size of the value
void *ht_it_get_value(hash_iterator *it, size_t *size);

// Destroy an iterator
void ht_it_destroy(hash_iterator *it);

#endif
        
