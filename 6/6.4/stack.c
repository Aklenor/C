#include <stdio.h>

extern void* malloc();
extern void free();

struct Stack{
    unsigned size;
    unsigned head;
    char* type;
    void** stack;
};

typedef struct Stack stack_t ;

struct Stack* StackInit(unsigned size){
    stack_t* header = malloc(sizeof(stack_t));
    void **stack = malloc(sizeof(void*) * size);
    for(register unsigned i=0; i<size;i++){
        stack[i] = NULL;
    }
    header->stack = stack;
    header->head = 0;
    header->size = size;
    header->type = NULL;
    return header;
}

void StackPush(void* ptr, struct Stack* stack){
    if( stack->head >= stack->size){
        printf("Stack owerflow\n");
        return;
    }
    stack->stack[stack->head++] = ptr;
}

void* StackPop(struct Stack* stack){
    if( stack->head == 0){
        printf("stack is empty\n");
        return NULL;
    }
    void* ptr = stack->stack[--stack->head];
    stack->stack[stack->head] = NULL;
    return ptr;
}

void StackPrint(struct Stack* stack){
    printf("size: %u, head: %u, type %s:\n[ ",
            stack->size, stack->head, stack->type);
    for(register unsigned i=0; i < stack->size; i++ ){
        printf("%p: %s,\n", &stack->stack[i], stack->stack[i]);
    }
    printf(" ]\n");
}

void StackFree(struct Stack* stack){
    for(register unsigned i=0; i<stack->size;i++){
        stack->stack[i] = NULL;
    }
    stack->size = 0;
    stack->head = 0;
    stack->type = NULL;
    free(stack->stack);
    free(stack);
}
