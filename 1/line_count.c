#include <stdio.h>

/* This program counts stuff */
/* versin 1 */

int main()
{
    int lines, tabs, spaces, sim;
    lines = 0;
    tabs = 0;
    spaces = 0;
    while ( (sim = getchar()) != EOF ){
        if (sim == ' ')
            ++spaces;
        if (sim == '\t')
            ++tabs;
        if (sim == '\n')
            ++lines;
    }
    printf("spaces: %3d\n", spaces);
    printf("tabs: %3d\n", tabs);
    printf("lines: %3d\n", lines);
    return 0;
}
