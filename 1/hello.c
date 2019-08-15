#include <stdio.h>

/* some multiline
comment */

void main ()
{
    float far, cels;
    int lower, upper, step;

    lower = 0;
    upper = 100;
    step = 10;

    far = lower;
    printf("farenheit to celsious\n");
    while( far <= upper ) {
        cels = (5.0/9.0) * ( far - 32.0 );
        printf("%3.0f\t%4.2f\n", far, cels);
        far = far + step;
    }
}
