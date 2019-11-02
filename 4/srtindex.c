#include <stdio.h>
#include "../1/my.h"

int strindex_r(char line[], int len, char target[]) {
    int j;
    for(int i=len;i>=0;i--){
        for(j=0;target[j] != '\0' && line[i+j] == target[j] && (i+j)<len; j++)
            ;
        if (target[j] == '\0')
            return i;
    }
    return -1;
}

int main() {
    int len;
    char target[] = "abc\0";
    char line[MAXLINE];
    while( (len=get_line(line, MAXLINE))>0) {
        printf("%d\n",strindex_r(line,len,target));
    }
    return 0;
}
