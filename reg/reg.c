#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFFSIZE 4096

int trans_endian(int big) {
    return ((big & 0xff) << 16) 
	   | (big & 0xff00) 
           | ((big & 0xff0000) >> 16);
}

int utf8_to_unicode(int utf8) {
    int high = (utf8 & 0xf0000) >> 16; 
    int middle = (utf8 & 0x3f00) >> 8;
    int low = utf8 & 0x3f;
    return (high << 12) | (middle << 6) | low; 
}

int is_chinese(int ch) {
    return (ch > 0x4E00 && ch < 0x9FCB)? 1: 0;  
}

int
main(int argc, char *argv[])
{
    int i;
    char buf[BUFFSIZE] = { 0 };

    int utf8;
    while (fgets(buf, BUFFSIZE, stdin)) {    
        i = 0;
        while(buf[i]) {
            if ((buf[i] & 0x80) == 0) { /* ascii字符 */
                if ((!isprint(buf[i])) && (buf[i] != '\n') && (buf[i] != '\r') ) {  /* 不可打印字符 */
                    goto clear;
                } 
                i++;
            } else { 
		((char *)&utf8)[0] = buf[i++];
		((char *)&utf8)[1] = buf[i++];
		((char *)&utf8)[2] = buf[i++];
		if (!is_chinese(utf8_to_unicode(trans_endian(utf8)))) { /*不是中文*/
		    goto clear;
		}
            }
        }
        if(buf[0]) {
            printf("%s",buf);
        }
        clear:
            memset(buf, 0, BUFFSIZE);
    } 
}
