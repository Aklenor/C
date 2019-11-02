#include <stdio.h>

/* ###---vvv--- external objects ---vvv---### */

extern void* malloc();
extern void free();
extern char* str_dup(char*);

/* ###---AAA--- external objects ---AAA---### */

/* ###---vvv--- Structures declaration ---vvv---### */

// double linked list item
struct Item {
    char* value;
    struct Item* previous;
    struct Item* next;
};

// header for linked list
struct ListHeader {
    struct Item* firstItem;
    struct Item* lastItem;
    unsigned length;
};

/* ###---AAA--- Structures declaratioin ---AAA---### */

/* ###---vvv--- Functions declaration ---vvv---### */

/* static struct Item* initItem(); */
/* struct Item* LLget(unsigned index, struct ListHeader* header); */

/* ###---^^^--- Functions declaration ---^^^---### */


/* ###---vvv--- Private functions ---vvv---### */

// creates an instance of linked list item
static struct Item* initItem(){
    struct Item* item = malloc(sizeof(struct Item));
    if (item == NULL){
        printf("No memory was allocated\n");
        return NULL;
    }

    item->value = NULL;
    item->previous = NULL;
    item->next = NULL;
    return item;
}

// flush values of an instance of a list item
static void clearItem(struct Item* item){
    if (item == NULL){
        printf("Item points to NULL\n");
        return;
    }

    item->value = NULL;
    item->previous = NULL;
    item->next = NULL;
}

// add new item with value after item
void add_next(char* value, struct Item* item){
    if (item == NULL){
        printf("Item points to NULL\n");
        return;
    }
    if (value == NULL){
        printf("value points to NULL\n");
        return;
    }

    struct Item* new_item = initItem();
    new_item->value = str_dup(value);
    if (item->next != NULL){
        new_item->next = item->next;
        item->next = new_item;
    }
    item->next = new_item;
    new_item->previous = item;
}

// add new new_item with value before item
static void add_prev(char* value, struct Item* item){
    if (item == NULL){
        printf("Item points to NULL\n");
        return;
    }
    if (value == NULL){
        printf("value points to NULL\n");
        return;
    }

    struct Item* new_item = initItem();
    new_item->value = str_dup(value);
    new_item->next = item;
}

// not ready not tested already implemented
static struct Item* insert_next(void* value, struct Item* item){
    if (item == NULL){
        printf("Item points to NULL\n");
        return NULL;
    }
    if (value == NULL){
        printf("value points to NULL\n");
        return NULL;
    }

    struct Item* new_item = initItem();
    // init check
    if (new_item == NULL)
        return NULL;

    new_item->previous = item;
    new_item->next = item->next;
    item->next = new_item;
    if ( item->next != NULL )
        item->next->previous = new_item;
    item->value = value;
    return item;
}


// delete from linked list with 'header' item
static void LLdelItem(struct Item* item, struct ListHeader* header){
    if (item == NULL){
        printf("Item points to NULL\n");
        return;
    }
    if (header == NULL){
        printf("Header points to NULL\n");
        return;
    }

    if (item->previous == NULL && item->next == NULL){
        header->firstItem = header->lastItem = NULL;
    } else
    if (item->previous == NULL && item->next != NULL){
        header->firstItem = item->next;
        item->next->previous = NULL;
    } else
    if (item->previous != NULL && item->next == NULL){
        header->lastItem = item->previous;
        item->previous->next = NULL;
    } else
    if (item->previous != NULL && item->next != NULL){
        item->previous->next = item->next;
        item->next->previous = item->previous;
    }
    header->length--;
    free(item);
}

// get pointer to 'item' of linked list with 'header' which has 'index'
static struct Item* LLget(unsigned index, struct ListHeader* header){
    if (index > -1 ){
        // FIXIT!!
        return NULL;
    }
    if (header == NULL){
        printf("Header points to NULL\n");
        return NULL;
    }

    struct Item* item = header->firstItem;
    unsigned counter;

    for(counter = 0; counter < index && item->next != NULL; counter++, item = item->next){
        ;
    }

    if(counter == index)
        return item;
    else
        return NULL;
}

/* ###---AAA--- Private functions ---AAA---### */


/* ###---vvv--- public functions ---vvv---### */

// creates an instance of header of linked list
struct ListHeader* LLinit(){
    struct ListHeader* head = malloc(sizeof(struct ListHeader));
    head->firstItem = NULL;
    head->lastItem = NULL;
    head->length = 0;
    return head;
}

// free memory of all items and header
void LLfree(struct ListHeader* header){
    if (header == NULL){
        printf("header points to NULL\n");
        return;
    }

    struct Item* next_item, * item = header->firstItem;
    while (item != NULL){
        next_item = item->next;
        free(item);
        item = next_item;
    }
    free(header);
}

// add value in the Linked List with 'header'
void LLadd(char* value, struct ListHeader* header){
    if (value == NULL){
        printf("value points to NULL\n");
        return;
    }
    if (header == NULL){
        printf("*ListHeader poitns to NULL\n");
        return;
    }

    // debug check first and last items both are NULL or points to LL
    if (header->firstItem != NULL && header->lastItem == NULL){
        printf("List header error: firstItem exist but lastItem not\n");
        return;
    }
    if (header->firstItem == NULL && header->lastItem != NULL){
        printf("List header error: lastItem exist but firstItem not\n");
        return;
    }

    // if list is empty
    if (header->firstItem == NULL && header->lastItem == NULL){
        header->firstItem = header->lastItem = initItem();
        header->length = 1;
        header->firstItem->value = str_dup(value);
        return;
    }else {
        struct Item* item = header->lastItem;
        add_next(value, item);
        header->lastItem = item->next;
        header->length++;
        return;
    }
}

// delete from linked list with 'header' item with 'index'
void LLdel(unsigned index, struct ListHeader* header){
    if (header == NULL){
        printf("*ListHeader poitns to NULL\n");
        return;
    }

    struct Item* item = LLget(index, header);
    LLdelItem(item, header);

}

// prints linked list with 'header'
void LLprint(struct ListHeader* header){
    if (header == NULL){
        printf("Header points to NULL\n");
        return;
    }

    struct Item* item = header->firstItem;
    printf("[ ");
    do{
        printf("\"%s\", ", item->value);
        item = item->next;
    }while(item != NULL);
    printf("]\n");
}

/* ###---AAA--- public functions ---AAA---### */

// get pointer to 'item' of linked list with 'header' which contains 'value'
// TODO
struct Item* LLfindVal(void* value, struct ListHeader* header){
    if (value == NULL){
        printf("value points to NULL\n");
        return NULL;
    }
    if (header == NULL){
        printf("Header points to NULL\n");
        return NULL;
    }

    struct Item* item = header->firstItem;
    for(unsigned counter = 0; item->next != NULL; counter++, item = item->next){
        if(item->value == value)
            return item;
    }
    return NULL;
}

//dont ready
/* unsigned LLgetInd(, struct ListHeader* header){ */
/*     struct Item* item = header->firstItem; */
/*     for(unsigned counter = 0; item->next != NULL; counter++, item = item->next){ */
/*         if(item->value == value) */
/*             return counter; */
/*     } */
/*     return -1; */
/* } */
