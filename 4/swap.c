#include <stdio.h>

#define swap(t,x,y) { t tmp = y; y=x; x=tmp; }

int main() {
    int x = 213;
    int y = 878;
    char a = 'a';
    char b = 'b';
    printf("int x,y: %d, %d\n", x, y);
    swap(int, x, y);
    printf("swap x,y: %d, %d\n", x, y);
    printf("char a,b: %c, %c\n", a, b);
    swap(int, a, b);
    printf("swap a,b: %c, %c\n", a, b);
    return 0;
}
