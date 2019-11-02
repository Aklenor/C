#include <stdio.h>
#include <ctype.h>
#include "mystr.c"
#include "WrdIndTree.c"

char getword(char* word, int lim);

int main() {

    int MAX_WORD_LEN = 100;
    char word[MAX_WORD_LEN];
    char sym;

    struct wrd_ind_tree *root = WITinit();

    unsigned line_counter = 1;
    while( (sym = getword(word, MAX_WORD_LEN)) != EOF){
        if (sym == '\n'){
            line_counter++;
            continue;
        }
        if(str_len(word) > 1)
            add_to_tree(word, root, line_counter);
    }

    print_tree(root);

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

    // check for EOL
    if (c == '\n'){
        return c;
    }

    // check for EOF
    if (c == EOF)
        return c;

    *word = '\0';
    return *--word;
}
