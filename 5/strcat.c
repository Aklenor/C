#include <stdio.h>
#include "../1/my.h"
#include "mylib.c"

/* void str_cat(char *a, char *b){ */
/*     for(; *a != '\0'; a++){ */
/*         ; */
/*     } */

/*     while( *b != '\0'){ */
/*         *a++ = *b++; */
/*     } */
/*     *a='\0'; */
/* } */

int main() {
    int len;
    char line[MAXLINE];
    char target[MAXLINE];
    printf("type first line:");
    get_line(target, MAXLINE);
    printf("type second line:");
    while((len = get_line(line, MAXLINE)) != 0){
        printf("before: %s\n", target);
        cat_str(target, line);
        printf("after: %s\n", target);
    }
    return 0;

}
