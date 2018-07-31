#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HASH_TABLE_MAX_SIZE (1 << 28)

typedef struct hashnode {
    unsigned long  hash; 
    int            next; 
} HashNode;

typedef struct hashtable {
    HashNode  *node;
    HashNode  *lastfree;
} HashTable;

void hash_table_init (HashTable *hashtable);

unsigned int hash_table_hash_str (const char* skey);

bool hash_table_insert_str (HashTable *hashtable, 
        const char* skey);


#endif /* !HASHTABLE_H */
