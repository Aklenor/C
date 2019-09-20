#define MAXLINE 1000
#define TAB_COLUMN_WIDTH 8

/* get_line: читает строку в line, возвращает длину */
int get_line(char line[], int lim){
    int sym, i;
    i = 0;
    while ( i < lim-1 && (sym = getchar()) != EOF && sym != '\n')
        line[i++] = sym;

    if (sym == '\n')
        line[i++] = sym;

    line[i] = '\0';
    return i;
}

/* copy: копирует из 'from' в 'to'; to достаточно большой */
void copy(char from[], char to[]){
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

void reverse(char line[]){
    int len,tail,head;
    char reverse_line[MAXLINE];
    reverse_line[MAXLINE-1] = '\0';

    len = 0;
    while (line[len] != '\0')
        len++;

    /* -1 because of last symbol is \n */
    tail = len - 1;
    for (head = 0; head < len; head++,tail--){
        /* printf("head: %d\tend: %d\tsym: %c\n",head,tail,line[tail]); */
        reverse_line[head] = line[tail];
    }

    reverse_line[head] = '\0';
    copy(reverse_line,line);
}

void shrink_spaces(char line[]){
    int i, j, sym;
    char fixed_line[MAXLINE];
    j = 0;
    for(i = 0; (sym = line[i]) != '\0'; ++i){
        if (sym != ' ' && sym != '\t'){
            fixed_line[j] = sym;
            ++j;
        }
        else if (fixed_line[j-1] != ' ' && j != 0 ){
            fixed_line[j] = ' ';
            ++j;
        }
    }
    if (fixed_line[j] == '\n')
    {
        fixed_line[j] = '\n';
        ++j;
    }

    fixed_line[j] = '\0';
    copy(fixed_line,line);
}

void detab(char line[],int len){
    int count, new_count = 0;
    char new_line[MAXLINE];

    for (count = 0; count <= len; ++count){
        if (line[count] == '\t'){
            /* it is necessary to execute loop at least once if current symbol
             is devided by TAB_COLUMN_WIDTH*/
            do {
                new_line[new_count] = ' ';
                ++new_count;
            } while ((new_count % TAB_COLUMN_WIDTH) != 0);
        }
        else {
            new_line[new_count] = line[count];
            ++new_count;
        }
    }

    copy(new_line,line);
}

void entab(char line[], int len){

    int count, new_count = 0; 
    char new_line[MAXLINE];
    int tabs = 0, spaces = 0;

    for (count = 0; count <= len; ++count){
        if (line[count] == ' '){

            /* printf("current symbol: %d",count); */ 
            /* count spaces and tabs till next nonspace symbol*/
            while (line[count+spaces] == ' '){
                ++spaces;
                if ((count+spaces % TAB_COLUMN_WIDTH) == 0)
                    ++tabs;
            }

            /* next round start from next nonspace symbol
               1 substitutes because of next round will add new*/
            count = count + spaces - 1;

            /* decrease number of spaces for tab replacement */
            spaces =  spaces - (tabs * TAB_COLUMN_WIDTH);


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

    copy(new_line,line);
}

void wrap(char line[], int len, int wrap_len){

    #define NO -1

    int last_space = NO;
    char new_line[MAXLINE];
    int len_count=0;

    for (int count=0, ncount=0; count <= len; ++count, ++ncount){

        new_line[ncount] = line[count];

        if (new_line[ncount] == ' ' || 
                new_line[ncount] == '\n'||
                new_line[ncount] == '\t')
            last_space = ncount;

        if (len_count >= wrap_len) {
            if(last_space != NO) {
                new_line[last_space] = '\n';
                len_count = ncount - last_space;
                last_space = NO;
            }
            else {
                new_line[ncount+1] = new_line[ncount];
                new_line[ncount] = '\n';
                ++ncount;
                last_space = NO;
                len_count = 1;
            }
        }
        else if (new_line[count] == '\t'){
            // correct tab to space calculation
            len_count = len_count + TAB_COLUMN_WIDTH -
                ((len_count + TAB_COLUMN_WIDTH) % TAB_COLUMN_WIDTH);
        }
        else
            ++len_count;
    }

    copy(new_line, line);
}
