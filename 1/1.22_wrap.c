#include <stdio.h>
#include "my.h"

void wrap(char line[], int len, int wrap_len){
    
    int last_space=0, sym;
    int new_count = 0, over = 0;
    char new_line[MAXLINE];

    for (int count=0; count <= len; ++count){

        if (line[count] == ' ')
            last_space = count;

        if (count > wrap_len){
            if (last_space != 0){
                new_line[last_space] = '\n';
            }
        }
        
        new_line[new_count] = line[count];
        ++new_count;
    }
    for (int i =0; i <=len; ++i){
        printf("%d|",new_line[i]);
        if (new_line[i] == '\0')
            break;
    }
    printf("\n");
    printf("%s",new_line);
    printf("___\n");
}

int main(){

    int len,i=0;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) != 0){
        printf("%s", line);
        wrap(line, len, 10);
        /* printf("%s",line); */
    }
    return 0;
}
