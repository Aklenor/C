#include <stdio.h>

/* This program counts shriks long sequence of spaces */
/* versin 1 */

int main()
{
    int sim, prev;
    prev = 0;
    while ( (sim = getchar()) != EOF ){
        if (sim != ' ' || prev != ' '){
            putchar(sim);
            prev = sim;
        }
    }
    return 0;
}
