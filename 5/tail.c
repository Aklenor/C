#include <stdio.h>
#include "gets.h"
#include "mem.h"
#include "mylib.c"

/* Add at the last NULL pointer in *ptr_array[] *new_elem */
/* if no NULL element - shift all values in array and add *new_elem to last. */
void fifo(char *ptr_array[], int arr_size, char *new_elem){
    /* check if there is free space */
    int last;
    for(last=0; ptr_array[last] != NULL; last++)
        ;

    if(last < arr_size){
        ptr_array[last] = new_elem;
        return;
    }
    int i;
    for(i=0; i<arr_size; i++){
        ptr_array[i] = ptr_array[i+1];
    }
    ptr_array[i-1] = new_elem;
}

int main(int argc, char *argv[]){
    char sym;
    int nlines = 10;

    while( --argc > 0 && (*++argv)[0] == '-'){
        while(( sym = *++argv[0] )) {
            int EXIT = 0;
            switch (sym){
                case 'n':
                    --argc;
                    argv++;
                    if ( *argv == NULL ){
                        printf("missed integer argument\n");
                        return 1;
                    }
                    if (!a2i( *argv, &nlines))
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

    int str_len;
    char line[MAXLINE];
    char *ptr;

    char *store[nlines];
    for(int i=0; i< nlines; i++)
        store[i] = NULL;

    for(int i=0; (str_len = get_line(line, MAXLINE)) != 0; i++ ){
        ptr = alloc(str_len);
        fifo(store, nlines, ptr);
        copy_str(line, ptr);
    }
    for(int j=0; j<nlines && store[j] != NULL; j++)
        printf("%s\n",store[j]);

    return 0;
}
