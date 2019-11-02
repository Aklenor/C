#include <stdio.h>
#include "gets.h"
#include "mylib.c"

#define MAXLINE 1000


int main(int argc, char *argv[]){
    int len;
    int width;
    char line[MAXLINE];
    char sym;

    while( --argc > 0 && (*++argv)[0] == '-'){
        while(( sym = *++argv[0] )) {
            int EXIT = 0;
            switch (sym){
                case 'w':
                    --argc;
                    argv++;
                    if ( *argv == NULL ){
                        printf("missed integer argument\n");
                        return 1;
                    }
                    if (!a2i( *argv, &width))
                        printf("argument: %s is not integer\n", *argv);
                    else
                        EXIT = 1;
                    break;

                default:
                    printf("'%s' is bad argument\n", *argv);
                    return 1;
            }
            if (EXIT)
                break;
       }
    }

    while ((len = get_line(line, MAXLINE)) != 0){
        entab(line, width);
        printf("tab width: %d\n",width);
        printf("%s\n", line);
    }
    return 0;
}
