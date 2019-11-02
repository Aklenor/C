#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void printBits(unsigned digit) {
    int size = sizeof(unsigned)*8;
    for(int bit = size-1; bit >=0; bit--) {
        printf("%d",(digit>>bit)&1);
    }
    printf("\n");
}

int qbitcount(int x) {
    int i;
    for (i=0;x != 0;i++)
        x &= (x-1);
    return i;
}
int main() {
    srand(time(NULL));
    int x = rand();
    printf("number: %d\n",x);
    printf("binary: ");
    printBits(x);
    printf("bits  : %d\n",qbitcount(x));
    return 0;
}
