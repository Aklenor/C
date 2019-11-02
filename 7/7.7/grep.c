#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///*---vvv--- extern ---vvv---*///{
///*---AAA--- extern ---AAA---*///}

typedef struct {
} t_flags;

typedef struct {
    char* name;
    FILE* file;
} file_list;

typedef struct{
    char* pattern;
    unsigned file_counter;
    file_list* files;
    t_flags flags;
} t_param;


///*---vvv--- local ---vvv---*///{
void parse_args(int argc, char **argv, t_param* params);
void free_params(t_param* params);
///*---AAA--- local ---AAA---*///}

int main(int argc, char** argv){
    t_param params;

    parse_args(argc, argv, &params);

    unsigned max_line_len = 65535;
    char line[max_line_len];
    for(register unsigned i=0; i<params.file_counter;i++){
        char* filename = params.files[i].name;
        unsigned line_count = 0;
        while( fgets(line, max_line_len, params.files[i].file) != NULL ){
           if( strstr( line,  params.pattern ) != NULL ){
               printf("%s [%u]: %s",filename, line_count, line);
           };
           line_count++;
        }
    }

    free_params(&params);
    exit(0);
}

void parse_args(int argc, char** argv, t_param* params){
    if( argc < 2 ){
        fprintf(stderr, "pattern not specified\n");
        exit(1);
    }

    // skip program name
    argc--;
    argv++;


    // get pattern
    params->pattern = *argv;
    argc--;
    argv++;

    //get files
    // allocate memory to store file descriptors and names
    params->files = (file_list*) calloc(argc, sizeof(file_list));

    if( argc < 1 ){
        params->file_counter=1;
        params->files[0].file = stdin;
        params->files[0].name = "stdin";
        return;
    }

    //get files
    params->file_counter=0;
    for (register unsigned i=0; i < (unsigned) argc; i++){
        params->files[i].name = argv[i];
        if( (params->files[i].file = fopen(argv[i], "r")) == NULL ){
            fprintf(stderr,"Can't open file '%s'\n", argv[i]);
        }else {
            params->file_counter++;
        }
    }
}

void free_params(t_param* params){
    for(register unsigned i=0; &params->files[i] != NULL && i<(params->file_counter); i++ ){
        fclose(params->files[i].file);
    }
    free(params->files);
}
