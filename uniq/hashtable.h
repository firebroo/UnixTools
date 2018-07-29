#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef bool
#   define bool           unsigned char
#endif

#ifndef false
#   define false          (0)
#endif

#ifndef true
#   define true           (!(false))
#endif

#define HASH_TABLE_MAX_SIZE (1 << 26)

#define hash_pos(skey) \
    hash_func((skey)) % HASH_TABLE_MAX_SIZE

#define hashTable_size(hashtable) \
    ((hashtable)->hash_size)

#define hashTable_max_size(hashtable) \
    (hashtable)->hash_table_max_size


#define mallocStr(str) \
    (char*) calloc (sizeof(char), strlen (str) + 1)



typedef struct hashnode HashNode;
struct hashnode {
    char      *sKey;
    HashNode  *pNext;
};

typedef struct hashtable {
    HashNode  *hashnode;
    size_t     hash_table_max_size;
    size_t     hash_size;
} HashTable;

void hash_table_init (HashTable *hashtable);

unsigned int hash_table_hash_str (const char* skey);

bool hash_table_insert_str (HashTable *hashtable, 
        const char* skey);

void hash_table_release (HashTable *hashtable);

#endif /* !HASHTABLE_H */
