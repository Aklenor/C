#include <stdio.h>
#include "../1/my.h"

void escape(char line[], int len) {
    char sym;
    char new_line[MAXLINE];
    for (int i=0,j=0; sym = line[i], i < len; i++)
        switch (sym){
            default:
                new_line[j++] = sym;
                break;
            case ' ':
                new_line[j++] = '\\';
                new_line[j++] = 's';
                break; 
            case '\a':
                new_line[j++] = '\\';
                new_line[j++] = 'a';
                break; 
            case '\b':
                new_line[j++] = '\\';
                new_line[j++] = 'b';
                break; 
            case '\n':
                new_line[j++] = '\\';
                new_line[j++] = 'n';
                break; 
            case '\t':
                new_line[j++] = '\\';
                new_line[j++] = 't';
                break; 
        }
    printf("%s", new_line);
}

int main() {
    int len;
    char line[MAXLINE];
    while ( (len=get_line(line, MAXLINE)) > 0 ){
        escape(line, len);
    }
}
