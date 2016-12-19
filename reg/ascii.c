#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFFSIZE 4096

int
main(int argc, char *argv[])
{
    int i;
    char buf[BUFFSIZE] = { 0 };

    while (fgets(buf, BUFFSIZE, stdin)) {    
        i = 0;
        while(buf[i]) {
            if ((!isprint(buf[i])) && (buf[i] != '\n') && (buf[i] != '\r') ) {  /* 不可打印字符 */
                goto clear;
            }
            i++;
        }
        if(buf[0]) {
            printf("%s",buf);
        }
        clear:
            memset(buf, 0, BUFFSIZE);
    } 
}
