#include <stdio.h>
#include <time.h>

int bin_search(unsigned long x, unsigned v[], unsigned long n) {
    int mid;
    int low = 0;
    int high = n-1;

    while( low <= high ) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid-1;
        else if (x > v[mid])
            low = mid+1;
        else
            return mid;
    }
    return -1;
}

int qbin_search(unsigned long x, unsigned v[], unsigned long n) {
    unsigned long mid;
    unsigned long low = 0;
    unsigned long high = n-1;

    while( low <= high ) {
        mid = (low + high) / 2;
        if (x <= v[mid])
            high = mid-1;
        else
            low = mid+1;
    }
    mid++;
    return (x == v[mid]) ? mid : -1;
}

#define ARR_MAX 1200000000
unsigned a[ARR_MAX];

int main() {
    /* #define unsigned long ARR_MAX 4000000 */ 
    clock_t start, end;
    for (unsigned long i = 0; i<ARR_MAX-1; i++)
        a[i] = i;

    unsigned elem;
    start = clock();
    elem = bin_search(1213234, a, ARR_MAX);
    end = clock();
    printf("return: %u, time: %ld\n", elem, end - start);

    start = clock();
    elem = qbin_search(1213234, a, ARR_MAX);
    end = clock();
    printf("return: %u, time: %ld\n", elem, end - start);

    return 0;
}
