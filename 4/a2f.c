#include <stdio.h>
#include <ctype.h>
#include "../1/my.h"

void printBits(unsigned long digit) {
    unsigned long int size = sizeof(unsigned long)*8;
    for(int bit = size-1; bit >=0; bit--) {
        printf("%lu",(digit>>bit)&1);
    }
    printf("\n");
}

double a2f(char line[], int len) {

    double val, power;

    int i; 
    int sign = 1;
    int e;
    float e_sign = 10;
    double e_power;

    for (i=0; isspace(line[i]) && i<len;i++)
        ;

    if (line[i] == '-'){
        sign=-1;
        i++;
    }
    else if (line[i] == '+'){
        sign=1;
        i++;
    }

    for (val = 0.0; isdigit(line[i]) && i<len; i++){
        val = 10.0 * val + (line[i] - '0');
        printf("%f\n", val);
    }

    if (line[i] == '.')
        i++;

    for (power = 1.0; isdigit(line[i]) && i<len; i++){
        val = 10.0 * val + (line[i] - '0');
        power *= 10.0;
        printf("%f power %f\n", val, power);
    }

    if (line[i] == 'e' || line[i] == 'E')
        i++;

    if (line[i] == '-'){
        e_sign=0.1;
        i++;
    }
    else if (line[i] == '+'){
        e_sign=10;
        i++;
    }

    for (e=0; isdigit(line[i]) && i<len; i++){
        e = 10.0 * e + (line[i] - '0');
        printf("%d\n", e);
    }

    for (e_power=1;e>0;e--){
        e_power=e_power*e_sign;
        printf("e_power: %lf\n",e_power);
    }

    return (sign*val/power)*e_power;
}

int main() {
    int len;
    double number;
    char line[MAXLINE];
    while ( (len=get_line(line,MAXLINE)) > 0 ) {
        number = a2f(line, len);
        printf("%lf\n",number);
        /* printBits( number ); */
    }
    return 0;
}
