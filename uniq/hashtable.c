#include "hashtable.h"


/* initialize hash table */
void
hash_table_init (HashTable *hashtable)
{
    hashtable->hash_table_max_size = HASH_TABLE_MAX_SIZE;
    hashtable->hash_size = 0;
    hashtable->hashnode = (HashNode *)calloc (sizeof(HashNode), \
            HASH_TABLE_MAX_SIZE);
}

HashNode*
create_new_node (const char *skey) {
    HashNode    *pNewNode;

    pNewNode = (HashNode*) malloc (sizeof (HashNode)); 
    pNewNode->sKey = mallocStr(skey);
    strcpy (pNewNode->sKey, skey);
    return pNewNode;
}


 unsigned long 
hash_func (const char *arKey)
{
    unsigned int nKeyLength = strlen(arKey);
	register unsigned long hash = 0;

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


/* string hash function */
/*
 * unsigned int
 * hash_table_hash_str (const char* skey)
 * {
 *     const char   *p;
 *         unsigned int  hash;
 *
 *             p = (const char*)skey;
 *                 hash = *p;
 *                     if (hash) {
 *                             for (p += 1; *p != '\0'; p++)
 *                                         hash = (hash << 5) - hash + *p;
 *                                             }
 *                                                 return hash;
 *                                                 }
 *                                                 */

/*insert key-value into hash table, if key is exist, 
 *  *it will overwrite old value, use link list to slove 
 *   *hash conflict,*/
bool
hash_table_insert_str (HashTable *hashtable, const char* skey)
{
    size_t          pos;
    HashNode       *pHead;
    HashNode       *pLast;
    HashNode       *pNewNode;

    pos = hash_pos(skey);
    pHead = hashtable->hashnode + pos;

    if (pHead->sKey) {
        do {
            if (strcmp (pHead->sKey, skey) == 0) {  
                return false; 
            }
            pLast = pHead;
        } while (pHead = pHead->pNext);
        pNewNode = create_new_node(skey);
        pLast->pNext = pNewNode;
    } else {
        pHead->sKey = mallocStr(skey);
        strcpy (pHead->sKey, skey);
    }
    return true;
}

