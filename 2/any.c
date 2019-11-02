#include <stdio.h>
#include <stdlib.h>
#include "../1/my.h"

/* return position of first element in line which equalst to one from syms*/ 
int any(char line[], char syms[]);

int main() {

    int len;
    char line[MAXLINE];
    char del_line[MAXLINE];
    while ((len = get_line(line, MAXLINE)) > 0){
        printf("remove chars:");
        get_line(del_line, MAXLINE);
        printf("%d", any(line, del_line));
    }

    return 0;
}

int any(char line[], char syms[]) {
    for (int i=0; line[i] != '\0'; ++i)
        for (int j=0; syms[j] != '\0'; ++j)
            if ( line[i] == syms[j] )
                return i;
    return -1;
}
