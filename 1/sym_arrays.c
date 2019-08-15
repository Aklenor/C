#include <stdio.h>

/* максимальный размер вводимой строки */
#define MAXLINE 1000

int get_line(char line[], int maxline);
void copy(char from[], char to[]);
 
/* печать самой длинной строки */
int main() 
{
    int len; /* длина текущей строки */
    int max; /* длина максимальной из просмотренных строк */
    char line[MAXLINE]; /* текущая строка */
    char longest[MAXLINE]; /* самая длинная строка */
    max = 0;
    while ((len = get_line(line, MAXLINE)) > 0){
        if (len > max)
        {
            max = len;
            copy(line, longest);
        }
    }

    if (max > 0) /* была ли хоть одна строка? */
        printf("%s", longest);
    return 0;
}
