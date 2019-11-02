#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include "../1/my.h"

void i2a(int n, char line[]){

    int i;
    int negative = (n < 0);
    i = 0;

    do{
        line[i++] = abs(n%10) + '0';
    }while( (n /= 10) != 0);

    if(negative)
        line[i++] = '-';
    line[i] = '\0';
    reverse(line);
}

void i2as(int n, char line[], int width){

    int i;
    int negative = (n < 0);
    i = 0;

    do{
        line[i++] = abs(n%10) + '0';
    }while( (n /= 10) != 0);

    if(negative)
        line[i++] = '-';
    while (i<width)
        line[i++] = ' ';
    line[i] = '\0';
    reverse(line);
}

void i2b(int n, char line[], int base){

    if(base > 62){
        printf("base too big");
    }

    char sym;
    int i;
    int negative = (n < 0);
    i = 0;

    do{
        sym=(abs(n%base));
        if (sym<10)
            sym += '0';
        else if (sym<36)
            sym += 'a'-10;
        else if (sym<62)
            sym += 'A'-36;
        else
            sym = '^';
        line[i++] = sym;
    }while( (n /= base) != 0);

    if(negative)
        line[i++] = '-';
    line[i] = '\0';
    reverse(line);
}

int main() {
#define MAX 2*INT_MAX
    int number;
    char line[MAXLINE];
    srand(time(NULL));
    for (int i=0; i<62; i++){
        number = rand()%1024-512;
        i2b(number, line, 62);
        printf("%d : %s\n", number, line);
    }

    return 0;
}
