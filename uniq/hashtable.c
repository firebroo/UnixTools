#include "hashtable.h"

/* initialize hash table */
void
hash_table_init (HashTable *hashtable)
{
    hashtable->hash_table_max_size = HASH_TABLE_MAX_SIZE;
    hashtable->hash_size = 0;
    hashtable->hashnode = (HashNode **)calloc (sizeof(HashNode*), \
            HASH_TABLE_MAX_SIZE);
}

/* string hash function */
unsigned int
hash_table_hash_str (const char* skey)
{
    const char   *p;
    unsigned int  hash;

    p = (const char*)skey;
    hash = *p;
    if (hash) {
        for (p += 1; *p != '\0'; p++)
            hash = (hash << 5) - hash + *p;
    }
    return hash;
}

/*insert key-value into hash table, if key is exist, 
 *it will overwrite old value, use link list to slove 
 *hash conflict,*/
bool
hash_table_insert_str (HashTable *hashtable, const char* skey)
{
    size_t          pos;
    HashNode       *pHead;
    HashNode       *pLast;
    HashNode       *pNewNode;

    pos = hash_pos (skey);
    pHead = (hashtable->hashnode)[pos];

    pNewNode = (HashNode*) malloc (sizeof (HashNode));
    pNewNode->sKey = mallocStr (skey);
    strcpy (pNewNode->sKey, skey);

    if (pHead) {
        while (pHead) {
            if (strcmp (pHead->sKey, skey) == 0) {  
                return false; 
            }
            pLast = pHead;
            pHead = pHead->pNext;
        }
        pLast->pNext = pNewNode;
    } else {
        (hashtable->hashnode)[pos] = pNewNode;
        hashtable->hash_size++;
    }
    return true;
}

/*free the memory of the hash table*/
void
hash_table_release (HashTable *hashtable)
{
    size_t      i;
    HashNode   *pHead, *pTemp;

    for (i = 0; i < hashtable->hash_table_max_size; i++) {
        if ((pHead = (hashtable->hashnode)[i])) {
            while (pHead) {
                pTemp = pHead;
                pHead = pHead->pNext;
                free (pTemp->sKey);
                free (pTemp);
            }
        }
    }
    free (hashtable->hashnode);
}
