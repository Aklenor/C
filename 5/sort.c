#include "sort.h"
#include <time.h>

int read_lines(char *ptr_array[], unsigned arr_size);
void print_lines(char **ptr_array, int nlines);

void qsort(char *v[], int left, int right, int (*cmp)(void *, void *));
void swap(char *v[], int i, int j);
int numcmp(char *line1, char *line2);

void ptr_reverse(char *ptr_array[], int size);

int main(int argc, char *argv[]) {

    int reverse = 0;
    int numeric_sort = 0;
    int case_insencitive = 0;
    char sym;

    while( --argc > 0 && (*++argv)[0] == '-'){
        while(( sym = *++argv[0] )) {
            switch (sym){
                case 'r':
                    reverse = 1;
                    break;

                case 'n':
                    numeric_sort = 1;
                    break;

                case 'i':
                    case_insencitive = 1;
                    break;

                default:
                    printf("'%s' is bad argument\n", *argv);
                    return 1;
            }
       }
    }

    unsigned max_strings = 100;
    unsigned last;
    char *str_ptr[max_strings];

    for (unsigned i=0; i<max_strings; i++)
        str_ptr[i] = NULL;

    if((last = read_lines(str_ptr, max_strings))<0)
        return 1;

    if(numeric_sort)
        qsort( str_ptr, 0, last-1, (int (*)(void *, void *))numcmp);
    else if (case_insencitive)
        qsort( str_ptr, 0, last-1, (int (*)(void *, void *))cmp_str_i);
    else
        qsort( str_ptr, 0, last-1, (int (*)(void *, void *))cmp_str);

    printf("----------\n");

    if (reverse)
        ptr_reverse( str_ptr, last);

    print_lines(str_ptr, last);

    return 0;
}

/* read lines to allocated memory in "mem.h" and store points in *ptr_array[] */
int read_lines(char *ptr_array[], unsigned arr_size){
    unsigned max_len = 81;
    unsigned len;
    unsigned nlines = 0;
    char line[max_len];
    char *storage;
    while( (len = get_line(line, max_len)) != 0 ){
        if ( (storage = alloc(len+1)) != NULL && nlines < arr_size){
            copy_str(line,storage);
            ptr_array[nlines++] = storage;
        } else{
            printf("not enough memory to store lines\n");
            return -1;
        }
    }
    return nlines;
}

/* print nlines from pointers array */
void print_lines(char **ptr_array, int nlines) {
    while(nlines-- > 0){
        printf("%s\n", *ptr_array++);
        /* printf("addr: %p ptr: %p\tval: %s\n", ptr_array, *ptr_array, *ptr_array); */
        /* ptr_array++; */
    }
}

/* qsort: сортирует v[left]...v[right] по возрастанию */
void qsort(char **v, int left, int right, int (*cmp)(void *, void *)) {

    int i, last;
    if (left >= right){ /* ничего не делается, если */
        return; /* в массиве менее двух элементов */
    }

    swap(v, left, (left + right)/2); /* делящий элемент */
    last = left; /* переносится в v[0] */

    for(i = left+1; i <= right; i++) /* деление на части */
        if ( cmp(v[i] , v[left]) < 0 )
            swap(v, ++last, i);

    swap(v, left, last); /* перезапоминаем делящий элемент */
    qsort(v, left, last-1, cmp);
    qsort(v, last+1, right, cmp);
}

/* swap: поменять местами v[i] и v[j] */
void swap(char *v[], int i, int j) {
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int numcmp(char *line1, char *line2){
    double atof(char *);
    double v1 = atof(line1);
    double v2 = atof(line2);
    return v1 - v2;
}

void ptr_reverse(char **head, int size){
    /* printf("reverse pointers\n"); */
    char **tail = head + size-1;
    char *tmp = NULL;
    /* printf("\thead(addr %p, ptr %p)\n", head, *head); */
    /* printf("\ttail(addr %p, ptr %p)\n", tail, *tail); */
    for(; head < tail ; head++, tail--){
        tmp = *head;
        /* printf("\ttmp = %p\n", *head); */
        *head = *tail;
        /* printf("\thead = %p\n", *tail); */
        *tail = tmp;
        /* printf("\ttail = %p\n", tmp); */
    }
}
