#include <stdio.h>

/* максимальный размер вводимой строки */
#define MAXLINE 1000

void copy(char from[], char to[]);
int get_line(char line[], int maxline);
void shrink_spaces(char line[]);
void reverse(char line[]);

/* печать самой длинной строки */
int main() 
{
    int len;
    char line[MAXLINE];
    while ((len = get_line(line, MAXLINE)) > 0)
    {
        reverse(line);
        printf("%s\n",line);
    }
    return 0;
}

/* get_line: читает строку в s, возвращает длину */
int get_line(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        /* printf("i: %d\t sym: %c\n",i,c); */
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

void shrink_spaces(char line[]) {
    int i, j, sym;
    char fixed_line[MAXLINE];
    j = 0;
    for(i = 0; (sym = line[i]) != '\0'; ++i){
        if (sym != ' ' && sym != '\t'){
            fixed_line[j] = sym;
            ++j;
        }
        else if (fixed_line[j-1] != ' ' && j != 0 ){
            fixed_line[j] = ' ';
            ++j;
        }
    }
    if (fixed_line[j] == '\n')
    {
        fixed_line[j] = '\n';
        ++j;
    }

    fixed_line[j] = '\0';
    copy(fixed_line,line);
}

void reverse(char line[])
{
    int len,tail,head;
    char reverse_line[MAXLINE];
    reverse_line[MAXLINE-1] = '\0';

    len = 0;
    while (line[len] != '\0')
        len++;

    /* -1 because of last symbol is \n */
    tail = len - 1;
    for (head = 0; head < len; head++,tail--){
        /* printf("head: %d\tend: %d\tsym: %c\n",head,tail,line[tail]); */
        reverse_line[head] = line[tail];
    }

    reverse_line[head] = '\0';
    copy(reverse_line,line);
}
