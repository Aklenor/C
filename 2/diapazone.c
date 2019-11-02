#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    printf("Unsigned char max: %d\n",UCHAR_MAX);
    printf("Signed char max: %d\n",SCHAR_MAX);
    printf("Signed char min: %d\n",SCHAR_MIN);
    printf("\n");

    printf("Unsigned int max: %u\n", UINT_MAX);
    printf("Signed int max: %d\n", INT_MAX);
    printf("Signed int min: %d\n", INT_MIN);
    printf("\n");

    printf("Unsigned long int max: %lu\n", ULONG_MAX);
    printf("Signed long int max: %ld\n", LONG_MAX);
    printf("Signed long int min: %ld\n", LONG_MIN);
    printf("\n");

    printf("Unsigned short int max: %u\n", USHRT_MAX);
    printf("Signed short int max: %d\n", SHRT_MAX);
    printf("Signed short int min: %d\n", SHRT_MIN);
    printf("\n");

    printf("Float max: %.20e\n", FLT_MAX);
    printf("Float min: %.20e\n", FLT_MIN);
    printf("Float epsilon: %.20e\n", FLT_EPSILON);
    printf("Float digits: %d\n", FLT_DIG);
    printf("\n");

    unsigned int i = ~0;
    printf("Unsigned int max: %u\n", i);
    printf("Signed int max: %d\n", i / 2);
    printf("Signed int min: %d\n",  - (i / 2) - 1);
    printf("\n");

    unsigned long int j = ~0;
    printf("Unsigned int max: %lu\n", j);
    printf("Signed int max: %ld\n", j / 2);
    printf("Signed int min: %ld\n",  - (j / 2) - 1);
    printf("\n");

    unsigned long long int k = ~0;
    printf("Unsigned long int max: %llu\n", k);
    printf("Signed long int max: %lld\n", k / 2);
    printf("Signed long int min: %lld\n",  - (k / 2) - 1);
    printf("\n");
}
