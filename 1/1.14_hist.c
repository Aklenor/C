#include <stdio.h>

int main()
{
    int c, i;
    int hist_char[256];

    for (i = 0; i<256; ++i)
        hist_char[i] = 0;

    while ((c=getchar()) != EOF)
        ++hist_char[c];

    for (i = 0; i<256; ++i)
    {
        int j;
        if (hist_char[i] != 0){
            printf("\"%c\"",i);
            for (j=0; j<hist_char[i]; ++j)
                printf("=");
            printf("\n");
        }
    }
    return 0;
}

