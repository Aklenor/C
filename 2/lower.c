#include <stdio.h>
#include "../1/my.h"

void lower(char line[], int len) {
    char new_line[MAXLINE];
    char sym;
    #define LOWER 'a' - 'A'
    for (int i=0; sym = line[i], i<=len; ++i)
        new_line[i] = ((sym>='A')&&(sym<='Z')) ? sym+LOWER : sym;
    copy(new_line, line);
}

int main() {
    char line[MAXLINE];
    int len;
    #define LOWER 'a' - 'A'
    printf("%d", LOWER);
    while ( (len=get_line(line, MAXLINE)) > 0){
        lower(line, len);
        printf("%s",line);
    }
    return 0;
}
