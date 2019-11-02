#include <stdio.h>

#include <ctype.h>

int main() {
    for(char c=0 ; c >= 0 ; c++){
        printf("%d: ", c);
        if(isprint(c))
            printf("%c\n", c);
        else
            printf("[]\n");
    }
}
