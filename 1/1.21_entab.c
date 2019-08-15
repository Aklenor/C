#include <stdio.h>
#include "my.h"

int main(){
    int len,i=0;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) != 0){
        entab(line, len);
        printf("%s",line);
    }
    return 0;
}
