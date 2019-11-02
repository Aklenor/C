#include "test.h"
#include <time.h>

void chsort(char *v[], int left, int right);
int read_lines(char *ptr_array[], unsigned maxlines);
void print_lines(char *ptr_array[], int nlines);
void swap(char *v[], int i, int j);

int main() {
    unsigned max = 10000;
    unsigned last;
    char *ptr[max];
    for (unsigned i=0; i<max; i++)
        ptr[i] = NULL;

    last = read_lines(ptr, max);

    chsort( ptr, 0, last-1);

    print_lines(ptr, last);

    return 0;
}

int read_lines(char *ptr_array[], unsigned maxlines){
    unsigned max_len = 181;
    unsigned len;
    unsigned nlines = 0;
    char line[max_len];
    char *storage;
    while( (len = get_line(line, max_len)) != 0 ){
        if ( (storage = alloc(len+1)) != NULL && nlines < maxlines){
            copy_str(line,storage);
            ptr_array[nlines++] = storage;
        } else{
            printf("not enough memory to store lines\n");
            return -1;
        }
    }
    return nlines;
}

void print_lines(char *ptr_array[], int nlines) {
    while(nlines-- > 0)
        printf("%s\n", *ptr_array++);
}

/* qsort: сортирует v[left]...v[right] по возрастанию */
void chsort(char *v[], int left, int right) {

    int i, last;
    if (left >= right){ /* ничего не делается, если */
        return; /* в массиве менее двух элементов */
    }

    swap(v, left, (left + right)/2); /* делящий элемент */
    last = left; /* переносится в v[0] */

    for(i = left+1; i <= right; i++) /* деление на части */
        if ( cmp_str(v[i] , v[left]) < 0 )
            swap(v, ++last, i);

    swap(v, left, last); /* перезапоминаем делящий элемент */
    chsort(v, left, last-1);
    chsort(v, last+1, right);
}

/* swap: поменять местами v[i] и v[j] */
void swap(char *v[], int i, int j) {
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


