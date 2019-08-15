#include <stdio.h>

/* print hystogram of thength of words */

#define IN_WORD 1
#define OUT_WORD 0

void main()
{
    int c, state, word_len;

    while ((c=getchar()) != EOF){
        if (c == ' ' || c == '\t' || c == '\n')
            state = OUT_WORD;
        else if (state == OUT_WORD){
            state = IN_WORD;
            printf("\n");
        }
        else
            printf("=");
    }
}
