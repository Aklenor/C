#include <stdio.h>

void main ()
{
    int c;
    while ((c = getchar()) != EOF) {
        printf( "\nstate = %c\n", EOF );
        putchar(c);
    }
}
