#include <stdio.h>
#include "stack.c"

/* #include "intLinkedList.c" */

/* ###---vvv--- external objects ---vvv---### */
// {
    extern void* malloc();
    extern char* str_dup(char*);
    extern char* str_dup_n(char*, unsigned);
    extern int str_cmp(char*, char*);
    #define true 1
// }
/* ###---AAA--- external objects ---AAA---### */

/* ###---vvv--- Structures declaratioin ---vvv---### */
// {

struct wrd_ind_tree {
    char* word;
    unsigned counter;
    struct wrd_ind_tree *junior_child;
    struct wrd_ind_tree *senior_child;
};

// }
/* ###---^^^--- Structures declaratioin ---^^^---### */

/* ###---vvv--- Functions declaration ---vvv---### */
// {

static struct wrd_ind_tree* node_alloc();
void add_to_tree(char *word, struct wrd_ind_tree *tree);
void print_tree(struct wrd_ind_tree* node);
struct wrd_ind_tree* init();

// }
/* ###---^^^--- Functions declaration ---^^^---### */

// clear node paramenters
static void clear_node(struct wrd_ind_tree* node){
    node->junior_child = NULL;
    node->senior_child = NULL;
    node->counter = 0;
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
void add_to_tree(char *word, struct wrd_ind_tree *node) {
    int cmp_state;
    if (node->word == NULL){
        node->word = str_dup(word);
        node->counter++;
        return;
    }
    cmp_state = str_cmp(word, node->word);
    if (cmp_state == 0){
        node->counter++;
    }
    else if(cmp_state < 0){
        if(node->junior_child == NULL){
            node->junior_child = node_alloc();
        }
        add_to_tree(word, node->junior_child);
    }
    else{
        if(node->senior_child == NULL){
            node->senior_child = node_alloc();
        }
        add_to_tree(word, node->senior_child);
    }

}

void print_tree(struct wrd_ind_tree *node) {
    if (node->word != NULL){
        print_tree( node->junior_child );
        printf("%s:\t%u\t", node->word, node->counter);
        print_tree( node->senior_child );
    }
}

unsigned count_nodes(struct wrd_ind_tree *node) {
    if( node == NULL)
        return 0;

    unsigned counter = 0;
    if( node->junior_child != NULL ){
        counter += count_nodes( node->junior_child );
    }
    if(node->senior_child != NULL){
        counter += count_nodes( node->senior_child );
    }
    counter++;
    return counter;
}

struct wrd_ind_tree** tree2list(struct wrd_ind_tree* root) {
    unsigned list_len = count_nodes(root);

    struct wrd_ind_tree** list = malloc(sizeof(struct wrd_ind_tree*) * (list_len+1));
    unsigned index = 0;
    for(unsigned i = 0; i<=list_len; i++){
        list[i] = NULL;
    }

    struct Stack* node_stack = StackInit(list_len); // for tree traversal
    struct wrd_ind_tree* current_node = root;

    while (true){
        while ( current_node != NULL){
            StackPush(current_node, node_stack);
            current_node = current_node->junior_child;
        }
        if( current_node == NULL && node_stack->head != 0){
            current_node = (struct wrd_ind_tree*) StackPop(node_stack);
            list[index++] = current_node;
            current_node = current_node->senior_child;
        }
        if( current_node == NULL && node_stack->head == 0)
            break;
    }

    /* for(unsigned i = 0; i<list_len; i++){ */
    /*     printf("%s\t[%u]\n", list[i]->word, list[i]->counter); */
    /* } */

    return list;
}
