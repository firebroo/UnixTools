#include "hashtable.h"

#define BUFFSIZE 4096

int
main (void)
{

    HashTable *hashtable = malloc (sizeof (HashTable));
    hash_table_init(hashtable);
    char buf[BUFFSIZE] = { 0 };

    while (fgets(buf, BUFFSIZE, stdin)) { 
        bool ret = hash_table_insert_str(hashtable, buf);
        if(ret) {
            printf("%s", buf);
        }
    }

    //hash_table_release(hashtable);
    free (hashtable);
    return 0;
}

