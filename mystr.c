#define MAXLINE 1000

#define abs(n) (n<0)? -1*n : n

extern void* malloc(long unsigned int);

void str_cat(char *a, char *b);
void str_cat_n(char *a, char *b, unsigned n);

int str_cmp(char *a, char *b);
int str_cmp_n(char *a, char *b, unsigned n);
int str_cmp_i(char *a, char *b);

void str_cp(char *from, char *to);
void str_cp_n(char *from, char *to, unsigned n);

void str_print(char *line);

char* str_dup(char* word);

int str_len(char *line);
void str_rev(char *line);

// concatenate a string '*a' with a string '*b'
void str_cat(char *a, char *b){
    // find last symbol
    for(; *a != '\0'; a++)
        ;

    do{
        *a++ = *b++;
    }while( *(b-1) != '\0');
}

// concatenate a string '*a' with 'n' symbols of a string '*b'
void str_cat_n(char *a, char *b, unsigned n){
    for(; *a != '\0'; a++)
        ;

    do{
        n--;
        *a++ = *b++;
    }while( *(b-1) != '\0' && n > 0);
}

// compare string a with string b
// returns residual between first found different components
int str_cmp(char *a, char *b){
    while( *a++ == *b++ ){
        if (*a == '\0' && *b == '\0')
            break;
    }
    return (*(a-1))-(*(b-1));
}

// compare 'n' symobls of a string 'a' with 'n' symbols of a string 'b'
// returns residual between first found different components
int str_cmp_n(char *a, char *b, unsigned n){
    while( *a++ == *b++ ) {
        n--;
        if ( *a == '\0' || *b == '\0' || n <=0)
            break;
    }
    return (*(a-1))-(*(b-1));
}

// compare a string 'a' with  a string 'b' case insencitive
int str_cmp_i(char *a, char *b){
    char A, B;
    do{
        A = (*a >= 0x61 && *a <= 0x7a)? *a - 0x20 : *a;
        B = (*b >= 0x61 && *b <= 0x7a)? *b - 0x20 : *b;
        /* printf("str_cmp_i() A: %c B:%c\n", A, B); */
        if (*(++a) == '\0' && *(++b) == '\0')
            break;
    }while( A == B );

    return A-B;
}

// copy string 'from' to string 'to'
void str_cp(char *from, char *to) {
    while( *from != '\0' ){
        *to++ = *from++;
    }
    *to = '\0';
}

// copy 'n' symbols of a string 'from' to a string 'to'
void str_cp_n(char *from, char *to, unsigned n) {
    while( *from != '\0' && n>0 ){
        *to++ = *from++;
        n--;
    }
    *to = '\0';
}

// allocates memory in heap for string 'word', copy string there and return a
// pointer
char* str_dup(char *word){
    char *ptr_word_store;
    ptr_word_store = malloc(str_len(word)+1);
    str_cp(word, ptr_word_store);
    return ptr_word_store;
}

// allocates memory in heap for 'n' symbols of a string 'word', copy that
// there and return a pointer
char* str_dup_n(char *word, unsigned n){
    char *ptr_word_store;
    ptr_word_store = malloc(n);
    str_cp_n(word, ptr_word_store, n);
    return ptr_word_store;
}

// print string as array
void str_print(char *line) {
    do{
        printf("%d|", *line++);
    }while(*(line-1) != '\0');
}

// translate integer 'number' to ascii string and put it in '*line'
void i2a(int number, char *line){
    int i=0;
    int negative = (number < 0);

    do{
        *line++ = abs( number%10 ) + '0';
    }while( (number /= 10) != 0);

    if(negative)
        line[i++] = '-';
    line[i] = '\0';
    str_rev(line);
}

// reverse order of symbols in '*line'
void str_rev(char *line) {
    char *tail = line + str_len(line)-2;
    char sym;
    while( line < tail ){
        sym = *line;
        *line++ = *tail;
        *tail-- = sym;
    }
}

// return length of '*line' string
int str_len(char *line){
    char *head = line;
    while( *line++ != '\0')
        ;
    return line - head;
}

// replace 'clmn_wdth' number of spaces with tab in string 'line'
void entab(char line[], int clmn_wdth){

    int len = str_len(line);
    int count, new_count = 0; 
    char new_line[MAXLINE];
    int tabs = 0, spaces = 0;

    for (count = 0; count <= len; ++count){
        if (line[count] == ' '){

            /* printf("current symbol: %d",count); */ 
            /* count spaces and tabs till next nonspace symbol*/
            while (line[count+spaces] == ' '){
                ++spaces;
                if ((count+spaces % clmn_wdth) == 0)
                    ++tabs;
            }

            /* next round start from next nonspace symbol
               1 substitutes because of next round will add new*/
            count = count + spaces - 1;

            /* decrease number of spaces for tab replacement */
            spaces =  spaces - (tabs * clmn_wdth);

            /* add tabs instead of spaces*/
            for(; tabs>0; --tabs){
                new_line[new_count] = '\t';
                ++new_count;
            }

            /* add rest spaces*/
            for(; spaces>0; --spaces){
                new_line[new_count] = ' ';
                ++new_count;
            }
        }
        else {
            new_line[new_count] = line[count];
            ++new_count;
        }
    }

    str_cp(new_line,line);
}

// try to get integer number from a '*str' and put in 'number_ptr'
// returns 0 in case of error and >0 in case of sucess
int a2i(char *str, int *number_ptr){
    char sym;
    int sign = 1;

    /* skip spaces */
    while( isspace(sym = *str++))
        ;

    if (!isdigit(sym) && sym !=EOF && sym != '+' && sym != '-'){
        return 0;
    }

    /* handle sign */
    if (sym == '-' || sym == '+'){
        sign = ( sym == '-' )? -1 : 1;
        sym = *str++;
        if ( !isdigit(sym) ){
                return 0;
            }
    }

    for(*number_ptr = 0; isdigit(sym); sym = *str++)
        *number_ptr = 10 * *number_ptr + (sym - '0');
    *number_ptr = sign * *number_ptr;

    /* if not end return last symbol to stdin in_buff[] */
    return 1;
}
