#include "wrdcount.h"

/* ###---vvv--- Structures declaratioin ---vvv---### */

struct prog_options {
    int group_of;
};


/* ###---^^^--- Structures declaratioin ---^^^---### */

/* ###---vvv--- Functions declaration ---vvv---### */

int parce_args(int argc, char **argv, struct prog_options *options);
int getword(char *word, int MAX_WORD_LEN);

/* ###---^^^--- Functions declaration ---^^^---### */

int main(int argc, char **argv) {
    struct prog_options opts;
    opts.group_of = 0;
    struct wrd_grp_tree* root = WGTinit();
    /* struct ListHeader* list = LLinit(); */

    parce_args(argc, argv, &opts);

    int MAX_WORD_LEN = 100;
    char word[MAX_WORD_LEN];

    while(getword(word, MAX_WORD_LEN) != EOF){
        if(slen(word) > 1)
            add_to_tree(word, root, opts.group_of);
    }

    print_tree(root);

}

int parce_args(int argc, char **argv, struct prog_options *options){
    size_t option;
    for (option = 1; option < (size_t) argc && argv[option][0] == '-'; option++){
        switch(argv[option][1]){
            case 'n':
                // get value for flag
                // check if there is more arguments available
                if (option >=  (size_t) argc){
                    printf("value for flag -%c not specified\n", argv[option][1]);
                    return 1;
                }
                // get next argument as value
                option++;
                if (a2i( argv[option], &options->group_of ) == 0){
                    printf("argument: %s is not integer\n", argv[option]);
                    return 1;
                }
                break;
            default :
                printf("'%s' is bad argument\n", *argv);
                return 1;
                break;
        }
    }
    return 0;
}

/* word can contain any letter, number or _,
 * could starts with the hash symbol;
 * text in double quotes parses by getquote();
 */
int getword(char *word, int lim) {
    char c;

    // skip spaces; do must skip not printable chars?
    while( isspace(c = getchar()) )
        ; 

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
