#include <stdio.h>
#include "my.h"

int main(){
    int len;
    char line[MAXLINE];
    while ((len = get_line(line, MAXLINE)) != 0){
        detab(line, len);
        printf("%s",line);
    }
    return 0;
}
