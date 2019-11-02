#include <stdio.h>
#include <math.h>
#include "../1/my.h"

int htol(char line[], int len) {

    char new_line[len];
    char c;

    if ( line[0] != '0' && (line[1] != 'x' || line[1] != 'X') ) {
        printf("\"%s\" is not a hexadecimal value\n", line);
        return 0;
    }
    int j = 0;
    for (int i=2; (c = line[i]) != '\0' && i < len-1;++i,++j){
        c = line[i];

        if      ( c >= '0' && c <= '9')
            new_line[j] = c - '0';
        else if ( c >= 'a' && c <= 'f')
            new_line[j] = c - 'a'+10;
        else if ( c >= 'A' && c <= 'F')
            new_line[j] = c - 'A'+10;
        else {
            printf("'%c' is not a legal value\n", c);
            return 0;
        }
    }
    int result = 0;
    for (int i=0; i<j; ++i){
        result = result + (int) pow(16, j-i-1)*new_line[i];
    }
    return result;
}

int main() {
    int len = 10;
    char line[123];
    while ((len = get_line(line, MAXLINE)) > 0){
        printf("%d\n",htol(line,len));
    }
}
