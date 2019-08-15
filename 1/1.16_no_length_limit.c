#include <stdio.h>

/* максимальный размер вводимой строки */
#define MAXLINE 10

void copy(char from[], char to[]);
int get_line(char line[], int maxline);
 
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

/* get_line: читает строку в s, возвращает длину */

int get_line(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}

/* copy: копирует из 'from' в 'to'; to достаточно большой */
void copy(char from[], char to[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

