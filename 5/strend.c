#include <stdio.h>
#include "../1/my.h"

int slen(char *line){
    char *head = line;
    while( *line++ != '\0')
        ;
    return line - head;
}

int strend(char *what, char *where){
    // find ends
    char *where_t = where + slen(where)-1;
    char *what_t = what + slen(what)-1;

    if ((what_t - what) > (where_t - where)){
        return -1;
    }

    while( *what_t-- == *where_t-- )
        if (what_t < what)
            return 1;

    return 0;
}

int main() {
    char line[MAXLINE];
    char target[MAXLINE] = "find me here\n";
    while( get_line(line, MAXLINE) != 0 ){
        printf("is '%s' in the end of '%s'? : %s\n", line, target, strend(line, target)? "yes\0":"no\0");
    }
    return 0;
}
