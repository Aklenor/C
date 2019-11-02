#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAX_OP 100
#define IS_NUM '0'
#define IS_OP '1'

#define MAX_STACK 100
double stack[MAX_STACK];
unsigned int s_top = 0;

#define MAX_REGS 52
double var_value[MAX_REGS];
char   var_key[MAX_REGS][MAX_OP];
int max_key = 0;

void var_put(double val, char name[]);
double var_get(char name[]);
void var_del(char name[]);

#define MAX_BUFFER 100
char buffer[MAX_BUFFER];
unsigned free_buff_pos = 0;

char get_word(char line[]);
char getch();
void ungetch(char);

void push(double value);
double pop(void);
void clear(void);

int isfloat(char line[]);
int comp(char a[], char b[]);

int main() {
    double tmp;
    char operation[MAX_OP];
    char variable[MAX_OP];
    while ( (get_word(operation)) != EOF) {
        if (isfloat(operation)){
            push( atof(operation) );
        }

        else if (comp(operation,"+")){
            /* printf("sum: %lf\n", pop() + pop()); */
            push( pop() + pop() );
        }

        else if (comp(operation,"*"))
            push( pop() * pop() );

        else if (comp(operation,"-")){
            tmp = pop();
            push( pop() - tmp );
        }

        else if (comp(operation,"/")){
            tmp = pop();
            push( pop() / tmp );
        }

        else if (comp(operation,"%")){
            tmp = pop();
            push( (int) pop() % (int)tmp );
        }

        else if (comp(operation,"\\"))
            clear();

        else if (comp(operation,"sin")){
            /* tmp = pop(); */
            /* printf("sin(%lf) = %lf\n",tmp, sin(tmp)); */
            push( sin(pop()) );
        }

        else if (comp(operation,"cos")){
            push( cos(pop()) );
        }

        else if (comp(operation,"tan")){
            push( tan(pop()) );
        }

        else if (comp(operation,"exp")){
            push( exp(pop()) );
        }

        else if (comp(operation,"pow")){
            tmp = pop();
            push( pow(pop(), tmp) );
        }

        else if (comp(operation,"pr")){
            tmp = pop();
            printf("%lf\n", tmp);
            push( tmp );
        }

        else if (comp(operation,"pop")){
            tmp = pop();
            printf("%lf\n", tmp);
        }

        else if (comp(operation,"ps")){
            for(unsigned i=0; i<s_top; i++)
                printf("%lf\n", stack[i]);
        }

        else if (comp(operation,"put")){
            get_word(variable);
            var_put(pop(), variable);
            ;
        }

        else if (comp(operation,"get")){
            get_word(variable);
            push(var_get(variable));
            ;
        }

        else if (comp(operation,"del")){
            get_word(variable);
            var_del(variable);
            ;
        }

        else
            printf("new varialbe: '%s'\n", operation);
            

        }
    return 0;
}

/* get_word puts it to line[]  returns type of symbol is operand or operator*/
char get_word(char line[]){
    char sym;
    #define MAX_WORD 20
    unsigned i; // line[i] item counter

    //skip prefix spaces
    while ( (sym = getch()) == ' ' || sym == '\t')
        ;

    line[0] = sym;
    for (i=1; (sym = getch()) != ' ' &&
            sym != '\t' && 
            sym != '\0' && 
            sym != '\n' && 
            i < MAX_WORD; i++ ){
        line[i] = sym;
    }
    line[i] = '\0';
    if (isfloat(line))
        return IS_NUM;
    else 
        return IS_OP;
}

char getch(void) {
    char sym;
    if (free_buff_pos > 0){
        /* printf("getch() free_buff_pos: %u > 0\n", free_buff_pos); */
        return buffer[--free_buff_pos];
    }
    else
        /* printf("getch() free_buff_pos: %u <= 0\n", free_buff_pos); */
        sym = (char) getc(stdin);
        return sym;
}

void ungetch(char sym) {
    /* printf("ungetch(%c)\n",sym); */
    if (free_buff_pos<MAX_BUFFER)
        buffer[free_buff_pos++] = sym;
    else
        printf("not enough space for '%c'",sym);
}

/* ###---vvv--- var Handle ---vvv---### */

int var_index(char name[]){
    for (int i=0; i < MAX_REGS; i++)
        if(comp(var_key[i],name))
            return i;
    return -1;
}

int var_add(char name[]){
    int index;
    for (index=0; ; index++)
        if (var_key[index][0] == '\0')
            break;
        if (index >= MAX_REGS){
            printf("no space to store variable: %s\n", name);
            return -1;
        }

    int i;
    for (i=0; i < MAX_OP && name[i] != '\0'; i++)
            var_key[index][i] = name[i];
    var_key[index][i] = '\0';
    return index;
}

void var_del(char name[]){
    int index = var_index(name);
    if (index == -1){
        printf("no such variable: %s\n",name);
        return;
    }

    for (int i=0; i < MAX_OP; i++)
            var_key[index][i] = '\0';
    var_value[index] = 0;
}

void var_put(double val, char name[]){
    int index = var_index(name);
    if (index == -1){
        index = var_add(name);
    }
    var_value[index] = val;
}

double var_get(char name[]){
    int index = var_index(name);
    if (index == -1){
        printf("no such variable: %s\n",name);
        return 0;
    }
    return var_value[index];
}

/* ###---^^^--- var Handle ---^^^---### */



/* ###---vvv--- command handle ---vvv---### */

int isfloat(char word[]){

    int i = 0;
    /* printf("is negative? [%c]:\n",word[i]); */
    if (word[i] == '-' || word[i] == '+'){
        i++;
        if (word[i] == '\0')
            return 0;
    }

    /* collect all integers */
    if (isdigit(word[i])){
        while (isdigit(word[i])){
            /* printf("collect all integers [%c]:\n",word[i]); */
            i++;
            ;
        }
    }

    /* collect all decimals */
    /* printf("is dot? [%c]:\n",word[i]); */
    if (word[i] == '.'){
        i++;
        if (isdigit(word[i]))
            while (isdigit(word[i])){
                /* printf("collect all decimals [%c]:\n",word[i]); */
                i++
                ;
            }
    }

    /* collect power part */
    /* printf("is e? [%c]:\n",word[i]); */
    if (word[i] == 'e' || word[i] == 'E' ){
        i++;
        /* printf("is + or -? [%c]:\n",word[i]); */
        if (word[i] == '-' ||
            word[i] == '+'){
            i++;
            /* printf("is digit? [%c]:\n",word[i]); */
            if (!isdigit(word[i])){
                /* printf("power with sign but without digit\n"); */
                return 0;
            }
        }
        if (isdigit(word[i]))
            while (isdigit(word[i])){
                /* printf("collect power [%c]:\n",word[i]); */
                i++;
            }
    }

    /* get EOL */
    /* printf("is EOL? [%c]:\n",word[i]); */
    if (word[i] == '\0')
        return 1;
    else
        return 0;
}

int comp(char a[], char b[]) {
    int i;
    for (i=0; a[i] != '\0' && b[i] != '\0'; ++i)
            if ( a[i] != b[i] )
                return 0;
    if ( a[i] != b[i] )
        return 0;
    else
        return 1;
}
/* ###---^^^--- command handle ---^^^---### */


/* ###---vvv--- Work With Stack ---vvv---### */

void push(double value) {
    if (s_top < MAX_STACK){
        stack[s_top++] = value;
        /* printf("push(), s_top: %d\n",s_top); */
    }
    else
        printf("not enough space in stack for '%lf'",value);
}

double pop() {
    /* printf("pop(): "); */
    if (s_top>0){
        /* printf("ok\n"); */
        return stack[--s_top];
    }
    else {
        printf("stack is empty\n");
        return 0.0;
    }
}

void clear(void) {
    s_top = 0;
}
/* ###---^^^--- Work With Stack ---^^^---### */
