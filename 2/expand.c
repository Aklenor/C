#include <stdio.h>
#include <ctype.h>
#include "../1/my.h"

void expand(char line[], int len) {
    int sym;
    char new_line[MAXLINE];
    char first;
    char mid;
    char last;
    int diff;

    for (int i=0,n=0; sym=line[i],i<=len; i++) {
        first = line[i];
        mid = line[(i+1)<=len ? (i+1) : '\0'];
        last = line[(i+2)<=len ? (i+2) : '\0'];

        if ( (mid == '-') &&
               ( (islower(first) && islower(last)) ||
                 (isupper(first) && isupper(last)) ||
                 (isdigit(first) && isdigit(last)) )
           ) {
            printf("expand: ");
            diff = last - first;
            if (diff > 0)
                for (char j=0; j <= diff && (i+j)<MAXLINE; j++){
                    new_line[n++] = first+j;
                    printf("%c", new_line[n-1]);
                }
            else
                for (char j=0; j >= diff && (i+j)<MAXLINE; j--){
                    new_line[n++] = first+j;
                    printf("%c", new_line[n-1]);
                }
            printf("\n");
            i += 2;
        }
        else
            new_line[n++] = sym;
    }
    printf("%s", new_line);
}

int main() {
    int len;
    char line[MAXLINE];
    while ((len=get_line(line, MAXLINE)) > 0) {
        expand(line, len);
    }
    return 0;
}
