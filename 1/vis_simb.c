#include <stdio.h>

/* This program changes spaces to _ tabs to \t backspace to \b and backslash to \\ */
/* versin 1 */

int main()
{
    int sim;
    while ( (sim = getchar()) != EOF ){
        if (sim == '\t'){
            putchar('\\');
            putchar('t');
        }
        /* how to input backspace??? */
        else if(sim == '\b'){
            putchar('\\');
            putchar('b');
        }
        else if (sim == ' ')
            putchar('_');
        else if (sim == '\\'){
            putchar('\\');
            putchar('\\');
        }
        else
            putchar(sim);
    }
    return 0;
}

