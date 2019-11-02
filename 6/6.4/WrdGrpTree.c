#include <stdio.h>

/* ###---vvv--- external objects ---vvv---### */

extern void* malloc();
extern char* str_dup(char*);
extern char* str_dup_n(char*, unsigned);
extern int cmp_str_n(char*, char*, unsigned);
/* extern void printf(void); */
extern struct ListHeader* LLinit();
extern void LLadd();
extern void LLprint();

/* ###---AAA--- external objects ---AAA---### */

/* ###---vvv--- Structures declaratioin ---vvv---### */

struct wrd_grp_tree {
    char* common;
    struct ListHeader* words;
    unsigned counter;
    struct wrd_grp_tree *junior_child;
    struct wrd_grp_tree *senior_child;
};

/* ###---^^^--- Structures declaratioin ---^^^---### */

/* ###---vvv--- Functions declaration ---vvv---### */

static struct wrd_grp_tree* node_alloc();
int add_to_tree(char *word, struct wrd_grp_tree *tree, unsigned cmp_size);
void print_tree(struct wrd_grp_tree* node);
struct wrd_grp_tree* init();

/* ###---^^^--- Functions declaration ---^^^---### */

// clear node paramenters
static void clear_node(struct wrd_grp_tree* node){
    node->common = NULL;
    node->counter = 0;
    node->junior_child = NULL;
    node->senior_child = NULL;
    node->words = NULL;
}

// allocate memory for the node tree
static struct wrd_grp_tree* node_alloc() {
    return (struct wrd_grp_tree *) malloc(sizeof(struct wrd_grp_tree));
}

struct wrd_grp_tree* WGTinit(){
    struct wrd_grp_tree* root = node_alloc();
    clear_node(root);
    return root;
}

// check if word is in the tree
// if yes - increase counter
// if not add to child_node
int add_to_tree(char *word, struct wrd_grp_tree *node, unsigned cmp_size) {
    int cmp_state;
    if (node->common == NULL){
        node->common = str_dup_n(word, cmp_size);
        node->words = LLinit();
        LLadd(word, node->words);
        node->counter = 1;
        node->junior_child = node_alloc();
        node->senior_child = node_alloc();
        return 1;
    }
    cmp_state = cmp_str_n(word, node->common, cmp_size);
    if (cmp_state == 0){
        LLadd(word,node->words);
        node->counter++;
    }
    else if(cmp_state < 0)
        add_to_tree(word, node->junior_child, cmp_size);
    else
        add_to_tree(word, node->senior_child, cmp_size);

    return node->counter;
}

void print_tree(struct wrd_grp_tree *node) {
    if (node->common != NULL){
        print_tree( node->junior_child );
        printf("%s:\t%d\n", node->common, node->counter);
        LLprint(node->words);
        print_tree( node->senior_child );
    }
}
