#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "../1/my.h"

void printBits(unsigned digit) {
    int size = sizeof(unsigned)*8;
    int arr[size];
    for(int bit = size-1; bit >=0; bit--) {
        arr[bit]=digit%2;
        digit = digit/2;
    }
    for(int i=0; i<size; i++)
        printf("%d",arr[i]);
    printf("\n");
}

// change n bits of x started from p with y */
unsigned setbits(unsigned x, int p, int n, unsigned y) {
    unsigned x_mask;
    unsigned y_mask;
    unsigned result;

    printf("x: %u\ny: %u\n",x,y);

    x_mask = ~(((~0x0)<<p)^(~0x0<<(p+n)));
    printf("x_mask: ");
    printBits(x_mask);

    y_mask = ( ~(~0x0<<(n)) ) ;
    printf("y_mask: ");
    printBits(y_mask);

    printf("x_mskd: ");
    printBits( x & x_mask );

    printf("y_mskd: ");
    printBits( (y & y_mask )<<p );

    result = (x & x_mask) | ((y & y_mask )<<p);
    printf("result: ");
    printBits( result );

    printf("result: %u\n", result);
    return result;
}

// invert n bits of x started from p
unsigned invert(unsigned x, int p, int n) {
    unsigned invert;
    unsigned x_mask;
    unsigned result;

    printf("x: %u\n",x);
    printf("x     : ");
    printBits(x);

    x_mask = ~(((~0)<<p)^(~0<<(p+n)));
    printf("x_mask: ");
    printBits(x_mask);

    invert = ((~(x & (~x_mask))) ^ x_mask);
    printf("invert: ");
    printBits(invert);

    printf("x_mskd: ");
    printBits( x & x_mask);

    result = ((x & x_mask) | invert);
    printf("result: ");
    printBits( result );

    printf("result: %u\n", result);
    return result;
}

unsigned rightrot(unsigned x, int n) {
    unsigned size=( sizeof(unsigned) * 8 );
    unsigned shifted;
    unsigned x_mask;
    unsigned result;

    printf("x     : ");
    printBits(x);

    if (n<0)
        n = size+n;

    x_mask = ~(~0<<n);
    printf("x_mask: ");
    printBits(x_mask);

    shifted = (x & x_mask)<<(size-n);
    printf("shiftd: ");
    printBits(shifted);

    result = (x>>n) | shifted;
    printf("result: ");
    printBits( result );
    return  result;
}

int main() {
    int position;
    int len;
    unsigned size=( sizeof(unsigned) * 8 );
    srand(time(NULL));
    position = rand()%(2*size)-size;
    if (position < 0)
        len = rand()%(size - ( ~position+1) );
    else
        len = rand()%(size - position);
    printf("posit: %d\n", position);
    printf("lngth: %d\n", len);
    setbits(rand(), position, len,rand());
    invert(rand(), position, len);
    rightrot(rand(), position);
    return 0;
}
