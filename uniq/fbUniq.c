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

#define BUFFSIZE 40


#define CHAR_SET_SIZE (1 << 30)

#define hash_pos(skey) \
    hash_func((skey)) % CHAR_SET_SIZE

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

int
main (void)
{

    char  buf[BUFFSIZE] = { 0 };
    char *charset = (char *)malloc(CHAR_SET_SIZE); 

    while (fgets(buf, BUFFSIZE, stdin)) { 
        int pos = hash_pos(buf);
        if (charset[pos]) {
            //pass
        } else {
            charset[pos] = 0x01;
            printf("%s", buf);
        }
    }

    //hash_table_release(hashtable);
    return 0;
}

