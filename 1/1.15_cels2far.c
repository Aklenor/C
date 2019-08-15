#include <stdio.h>

#define LOWER 0
#define UPPER 100
#define STEP 1

int celsius_2_faringate(int celsius);

void main ()
{
    float cels;
    printf("celsius to farengheit\n");
    for(cels = UPPER; cels >= LOWER; cels = cels - STEP){
        printf("%3.0f\t%4.2f\n", cels, celsius_2_faringate(cels) );
    }
}

int celsius_2_faringate(int celsius)
{
    return (9.0/5.0)*celsius + 32.0;
}
