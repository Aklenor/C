#define SIZE 10000000

char buffer[SIZE];
char *buffer_top = buffer;

char *alloc(unsigned size){
    if( buffer_top+size <= buffer+SIZE ){
        buffer_top += size;
        return buffer_top - size;
    }
    else {
        return 0;
    }
}

void free(char *ptr){
    if ( ptr > buffer && ptr < buffer_top )
        buffer_top = ptr;
}
