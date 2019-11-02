#include <stdio.h>
#include <stdlib.h>
#include "../1/my.h"

void squeeze(char line[], char syms[]) {
    #define SKIP 0
    #define COPY 1
    int i;
    int state=COPY;
    int count = 0;
    char new_line[MAXLINE];
    for (i=0; line[i] != '\0'; ++i){
        state=COPY;
        for (int j=0; syms[j] != '\0'; ++j)
            if ( line[i] == syms[j] ) {
                state = SKIP;
                break;
            }
        if (state == COPY){
            new_line[count++] = line[i];
        }
    }
    new_line[count] = '\0';
    copy( new_line, line);
}

int main() {

    int len;
    /* int del[MAXLINE] = {2,4,6}; */
    char line[MAXLINE];
    char del_line[MAXLINE];
    while ((len = get_line(line, MAXLINE)) > 0){
        printf("remove chars:");
        get_line(del_line, MAXLINE);
        squeeze(line, del_line);
        printf("%s",line);
    }

    return 0;
}
