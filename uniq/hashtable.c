#include "hashtable.h"

/* initialize hash table */
void
hash_table_init (HashTable *hashtable)
{
    hashtable->node = (HashNode *)calloc (sizeof(HashNode), \
            HASH_TABLE_MAX_SIZE);
    hashtable->lastfree = hashtable->node;
}

unsigned long 
hash_func (const char *arKey)
{
    unsigned int nKeyLength = strlen(arKey);
	register unsigned long hash = 5381;

	/* variant with the hash unrolled eight times */
	for (; nKeyLength >= 8; nKeyLength -= 8) {
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
		hash = ((hash << 5) + hash) + *arKey++;
	}
	switch (nKeyLength) {
		case 7: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
		case 6: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
		case 5: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
		case 4: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
		case 3: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
		case 2: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
		case 1: hash = ((hash << 5) + hash) + *arKey++; break;
		case 0: break;
	}
	return hash;
}


bool
hash_table_insert_str (HashTable *hashtable, const char* skey)
{
    size_t          pos;
    HashNode       *pHead;
    HashNode       *pLast;
    HashNode       *lastfree;
    unsigned long   hashv;
    
    hashv = hash_func(skey);
    pos = hashv % HASH_TABLE_MAX_SIZE;
    pHead = hashtable->node + pos;
    lastfree = hashtable->lastfree;

    if (pHead->hash) {
        if (pHead->hash == hashv) {
            do {
                if (pHead->hash == hashv) {  
                    return false; 
                }
                pLast = pHead;
                pHead = hashtable->node + pHead->next;
            } while (pHead->next);
            lastfree->hash = pHead->hash;
            pLast->next = (lastfree-(hashtable->node))/sizeof(HashNode);
        } else {
            lastfree->hash = pHead->hash;
            pHead->hash = hashv;
        }
    } else {
        pHead->hash = hashv;
    }

    while (lastfree->hash == 0L) { 
        lastfree++;
    }
    hashtable->lastfree = lastfree;
    return true;
}

