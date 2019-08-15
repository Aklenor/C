#include <stdio.h>

#define LOWER 0
#define UPPER 100
#define STEP 1

void main ()
{
    float cels;
    printf("celsius to farengheit\n");
    for(cels = UPPER; cels >= LOWER; cels = cels - STEP){
        printf("%3.0f\t%4.2f\n", cels, (9.0/5.0)*cels + 32.0 );
    }
}
