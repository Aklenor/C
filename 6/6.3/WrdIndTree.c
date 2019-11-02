#include <stdio.h>
#include "intLinkedList.c"

/* ###---vvv--- external objects ---vvv---### */
// {
    extern void* malloc();
    extern char* str_dup(char*);
    extern char* str_dup_n(char*, unsigned);
    extern int str_cmp(char*, char*);
    /* extern int cmp_str_n(char*, char*, unsigned); */
    /* extern void printf(void); */
    extern struct ListHeader* LLinit();
    extern void LLadd();
    extern void LLprint();
// }
/* ###---AAA--- external objects ---AAA---### */

/* ###---vvv--- Structures declaratioin ---vvv---### */
// {

struct wrd_ind_tree {
    char* word;
    struct ListHeader* lines;
    struct wrd_ind_tree *junior_child;
    struct wrd_ind_tree *senior_child;
};

// }
/* ###---^^^--- Structures declaratioin ---^^^---### */

/* ###---vvv--- Functions declaration ---vvv---### */
// {

static struct wrd_ind_tree* node_alloc();
void add_to_tree(char *word, struct wrd_ind_tree *tree, unsigned cmp_size);
void print_tree(struct wrd_ind_tree* node);
struct wrd_ind_tree* init();

// }
/* ###---^^^--- Functions declaration ---^^^---### */

// clear node paramenters
static void clear_node(struct wrd_ind_tree* node){
    node->junior_child = NULL;
    node->senior_child = NULL;
    node->lines = NULL;
    node->word = NULL;
}

// allocate memory for the node tree
static struct wrd_ind_tree* node_alloc() {
    return (struct wrd_ind_tree *) malloc(sizeof(struct wrd_ind_tree));
}

struct wrd_ind_tree* WITinit(){
    struct wrd_ind_tree* root = node_alloc();
    clear_node(root);
    return root;
}

// check if word is in the tree
// if yes - add line
// if not add to child_node
void add_to_tree(char *word, struct wrd_ind_tree *node, unsigned line) {
    int cmp_state;
    if (node->word == NULL){
        node->word = str_dup(word);
        node->lines = LLinit();
        LLadd(line, node->lines);
        node->junior_child = node_alloc();
        node->senior_child = node_alloc();
        return;
    }
    cmp_state = str_cmp(word, node->word);
    if (cmp_state == 0){
        LLadd(line, node->lines);
    }
    else if(cmp_state < 0)
        add_to_tree(word, node->junior_child, line);
    else
        add_to_tree(word, node->senior_child, line);

}

void print_tree(struct wrd_ind_tree *node) {
    if (node->word != NULL){
        print_tree( node->junior_child );
        printf("%s:\t%u\t", node->word, node->lines->length);
        LLprint(node->lines);
        print_tree( node->senior_child );
    }
}

unsigned count_nodes(struct wrd_ind_tree *node) {
    unsigned counter = 0;
    if (node->word != NULL){
        count_nodes( node->junior_child );
        counter++;
        count_nodes( node->senior_child );
    }
    return counter;
}

struct ListHeader* tree2list(struct wrd_ind_tree* root) {
    
}

void print_tree_hst(struct wrd_ind_tree *root) {
    unsigned node_number = count_nodes(root);
    struct wrd_ind_tree* hst[node_number];
}
