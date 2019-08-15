#include <stdio.h>

#define IN 1
#define OUT 0

/* print words from getchar() one by line */

int main()
{
    int c, state;
    state = IN;
    while ( (c = getchar()) != EOF ){
        if (c == ' ' || c == '\t' || c == '\n')
            state = OUT;
        else if ( state == OUT ){
            state = IN;
            printf("\n");
        }
        if (state == IN)
            printf("%c",c);
    }
    return 0;
}

