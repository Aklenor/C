#define MAX_BUFFER 1000

static char in_buff[MAX_BUFFER];
static unsigned free_buff_pos=0;

static char getch(void) {
    char sym;
    if (free_buff_pos > 0){
        return in_buff[--free_buff_pos];
    }
    else
        sym = (char) getc(stdin);
        return sym;
}

static void ungetch(char sym) {
    if (free_buff_pos<MAX_BUFFER)
        in_buff[free_buff_pos++] = sym;
    else
        printf("not enough space for '%c'",sym);
}

int get_line(char *line, unsigned limit) {
    char *line_head = line;
    char *line_tail = line+limit;
    int sym;
    while ( line < line_tail && (sym = getch()) != EOF && sym !='\n')
        *line++ = sym;

    if (sym != EOF)
        *line++ = '\0';

    return line-line_head;
}

char getfloat(double *num_ptr){
    char sym;

    int sign = 1;
    int integer=0;
    int decimal=0;
    double dec_pow=1;
    double power=1;
    double power_sign=1;
    char e_sym; //use to stor 'e' or 'E'

    /* skip spaces */
    while( isspace(sym = getch()) )
        ;

    if (sym != '-' &&
        sym != '+' &&
        !isdigit(sym) &&
        sym != '.' &&
        sym != 'e' &&
        sym != 'E' &&
        sym != EOF) {
        ungetch(sym);
        return 0;
    }

    /* get sign */
    if (sym == '+' || sym == '-'){
        sign = (sym == '-')? -1 : 1;
        sym=getch();
        /* after sign should be [0-9|.|e|E] else exit */
        if ( !isdigit(sym) && sym != '.' && sym != 'e' && sym != 'E'){
            ungetch(sym); //return back that illegal symbol
            ungetch( (sign == -1)? '-' : '+'); //return back sign
            return 0;
        }
    }

    /* get integer part */
    if(isdigit(sym)){
        for(integer = 0; isdigit(sym); sym = getch()){
            integer = 10*integer + (sym - '0');
        }
        /* if next symbol is illegal calculate result */
        if ( sym != '.' && sym != 'e' && sym != 'E' && sym != EOF){
            ungetch(sym);
            goto calc_result;
        }
    }

    /* get dot */
    if (sym == '.'){
        sym=getch();
        /* get decimal part */
        for(decimal=0, dec_pow=1.0; isdigit(sym); sym = getch(), dec_pow*=0.1){
            printf("\tgetfloat(): dec_pow: %lf\n", dec_pow);
            decimal = 10*decimal + (sym - '0');
        }
        /* if next symbol is illegal calculate result */
        if ( sym != '.' && sym != 'e' && sym != 'E' && sym != EOF){
            ungetch(sym);
            goto calc_result;
        }
    }

    if (sym == 'e' || sym == 'E'){
        e_sym = sym;
        sym = getch();
        if ( !isdigit(sym) && sym != '-' && sym != '+' ){
            ungetch(sym);
            ungetch(e_sym);
            goto calc_result;
        }
        if (sym == '+' || sym == '-'){
            power_sign = (sym == '-')? 0.1 : 10;
            sym=getch();
            /* after sign should be [0-9] else exit */
            if ( !isdigit(sym) ){
                ungetch(sym);
                ungetch( (power_sign == 0.1)? '-' : '+' );
                ungetch(e_sym);
                goto calc_result;
            }
        }
        if ( !isdigit(sym) ){
            ungetch(sym);
            ungetch(e_sym);
            return 0;
        }

        /* get power */
        for(power = 0; isdigit(sym); sym = getch()){
            power = 10*power + (sym - '0');
        }
        printf("\tgetfloat(): power: %lf\n", power);
        double tmp=1.0;
        for(;power>0;power--)
            tmp *= power_sign;
        power = tmp;
        goto calc_result;
    }

    calc_result:{
        printf("sign: %d\n", sign); 
        printf("integer: %d\n", integer);
        printf("decimal: %d\n",decimal);
        printf("dec_pow: %lf\n",dec_pow);
        printf("pow_sig: %lf\n",power_sign);
        printf("power: %lf\n",power);
        *num_ptr = (sign*integer + (decimal*dec_pow))*power;

        /* if not end return last symbol to stdin in_buff[] */
        if (sym != EOF)
            ungetch(sym);
        return sym;
    }
}

char getint(int *number_ptr){

    char sym;
    int sign = 1;
    /* skip spaces */
    while( isspace(sym = getch()))
        ;

    if (!isdigit(sym) && sym !=EOF && sym != '+' && sym != '-'){
        ungetch(sym);
        return 0;
    }

    /* handle sign */
    if (sym == '-' || sym == '+'){
        sign = ( sym == '-' )? -1 : 1;
        sym = getch();
        if ( !isdigit(sym) ){
                ungetch(sym);
                ungetch( (sign == -1)? '-' : '+');
                return 0;
            }
    }

    for(*number_ptr = 0; isdigit(sym); sym = getch())
        *number_ptr = 10 * *number_ptr + (sym - '0');
    *number_ptr = sign * *number_ptr;

    /* if not end return last symbol to stdin in_buff[] */
    if (sym != EOF)
        ungetch(sym);
    return sym;
}
