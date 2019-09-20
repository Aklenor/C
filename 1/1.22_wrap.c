#include <stdio.h>
#include "my.h"

int main(){

    int len,i=0;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) != 0){
        /* printf("%s", line); */
        wrap(line, len, 20);
        printf("%s",line);
    }
    return 0;
}
