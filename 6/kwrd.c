#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../5/gets.h"
#include "../5/mylib.c"

#define MAXWORD 100

struct key {
    char *word;
    int count;
} keytab[] = {
    {"\"string const\"", 0},
    {"#preprocess words",0},
    {"/*comment*/", 0},
    {"//comment", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"int", 0},
    {"unsigned", 0},
    {"void", 0},
    {"while", 0}
};

#define NKEYS ( sizeof(keytab) / sizeof(struct key) )

int getword(char *, int);
int qbin_search(char *word, struct key tab[], unsigned n);

int main(/*int argc, char *argv[]*/) {
    int n=0;
    char word[MAXWORD];

    while( getword(word, MAXWORD) != EOF){
        n = qbin_search( word, keytab, NKEYS);
        /* printf("%s: %d\n",word, n); */
        if (n >= 0)
            keytab[n].count++;
    }
    for(unsigned key_word=0; key_word < NKEYS; key_word++){
        printf("%s [%d]\n", keytab[key_word].word, keytab[key_word].count );
    }

}

int qbin_search(char *word, struct key tab[], unsigned n) {
    /* int cmp_str(char *word_a, char *word_b); */
    int state;
    int mid;
    int low = 0;
    int high = n-1;

    while( low <= high ) {
        mid = (low + high) / 2;
        /* printf("low: %d\tmid: %d\thigh: %d\n", low, mid, high); */
        state = cmp_str( word, tab[mid].word);
        /* printf("\tstate: %d\n", state); */
        if(state < 0)
            high = mid-1;
        else if (state > 0)
            low = mid+1;
        else
            return mid;
    }
    return -1;
}

/* TODO add "string constant" handling */
/* use stack? */
/* get all symbols till next double quote */
/* TODO comment handling */
/* TODO preprocess commands handling */
int getword(char *word, int lim) {
    char *word_head = word;
    char c;
    while( isspace(c = getchar()) )
        ;

    if (c != EOF)
        *word++ = c;

    /* handle string constants */
    if ( c == '"' ){
        *word++ = c;
        do{
            *word++ = c = getchar();
            if(c == EOF ) {
                printf("ERROR: unexpected EOF; "
                        "missed terminating '\"' character\n");
                return c;
            }
            if(c == '\n' ) {
                printf("ERROR: unexpected EOL; "
                        "missed terminating '\"' character\n");
                return c;
            }
            if( c == '\\' && (c = getchar()) != EOF) {
                *word++ = c;
            }
        }while( c != '"');
        copy_str("\"string const\"", word_head);
        return c;
    }

    /* handle preprocess strings */
    if ( c == '#' ){
        while( isalpha(c=getchar()) );
        copy_str("#preprocess words\0", word_head);
        return c;
    }

    /* handle comments */
    if ( c == '/' ){
        *word++=c=getchar();
        if ( c == '/' ){
            /* skilp all chars till EOL */
            while( (c=getchar()) != '\n' && c != EOF )
                ;
            copy_str("//comment", word_head);
            return c;
        }else if ( c == '*' ){
            /* skip all chars till end of comment */
            while( 1 ){
                c = getchar();
                if(c==EOF){
                    printf("ERROR: unexpected EOL; "
                            "missed terminating '*/' comment\n");
                    return c;
                }
                /* catch terminating comment */
                if( c == '*'){
                    c = getchar();
                    if( c == '/'){
                        copy_str("/*comment*/", word_head);
                        return c;
                    }else if(c==EOF){
                        printf("ERROR: unexpected EOL; "
                                "missed terminating '*/' comment\n");
                        return c;
                    }
                }
            }
        }
    }

    if ( !isalpha(c) && c != '_' ){
        *word = '\0';
        return c;
    }

    for(; --lim>0; word++)
        if( !isalpha(*word = getchar()) && c != '_'){
            ungetc(*word, stdin);
            break;
        }
    *word = '\0';
    return word[0];
}
