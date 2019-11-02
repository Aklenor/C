#include <stdio.h>
#include <ctype.h>
#include "mystr.c"
#include "WrdIndTree.c"

char getword(char* word, int lim);
void qsort(void *v[], int left, int right, int (*cmp)(void *, void *));
void swap(void *v[], int i, int j);
int wit_cmp(struct wrd_ind_tree *a,struct wrd_ind_tree *b);

int main() {

    int MAX_WORD_LEN = 100;
    char word[MAX_WORD_LEN];
    char sym;

    struct wrd_ind_tree *tree = WITinit();

    while( (sym = getword(word, MAX_WORD_LEN)) != EOF){
        if(str_len(word) > 1){
            add_to_tree(word, tree);
        }
    }

    struct wrd_ind_tree** word_list = tree2list(tree);
    unsigned list_length=0;

    for(unsigned i=0; word_list[i] != NULL; i++){
        /* printf("ptr:%p;\twrd:%12s;\tcnt:%u;\n", */ 
        /*         *word_list, (*word_list)->word, (*word_list)->counter); */
        list_length++;
    }

    qsort((void **) word_list, 0, list_length-1, (int (*)(void *,void *))wit_cmp);

    for(unsigned i=0; i < list_length; i++){
        printf("ptr:%p;\twrd:%12s;\tcnt:%u;\n", 
                word_list[i], word_list[i]->word, word_list[i]->counter);
    }

    return 0;
}


char getword(char *word, int lim) {
    char c = getchar();

    // skip spaces;
    // is it skip new line char?
    while( isspace(c) && c != '\n' )
        c = getchar();

    //if c is '"' getquote()

    //if c is digit getdigit()

    // word could start with '#' symbol
    if (c == '#'){
        *word++ = c;
        c = getchar();
    }

    // --lim>1 because one last symbol for \0
    for(; --lim>1; c = getchar(), word++){
        if( !isalpha(c) && !isdigit(c) &&c != '_' ){
            break;
        }
        *word = c;
    }

    // check for EOF
    if (c == EOF)
        return c;

    *word = '\0';
    return *--word;
}

void qsort(void* v[], int left, int right, int (*cmp)(void *, void *)) {

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
void swap(void* v[], int i, int j) {
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// compare two node of the wrd_ind_tree by counter
int wit_cmp(struct wrd_ind_tree* a,struct wrd_ind_tree* b){
    return ((int) a->counter - (int) b->counter) * -1;
}
