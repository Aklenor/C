
#include <stdio.h>
#include <string.h>

extern void exit(int);

struct parameters {
    FILE* file1;
    FILE* file2;
} parameters;

int parce_args(int argc, char **argv, struct parameters *parameters);

int main(int argc, char** argv){
    parce_args(argc, argv, &parameters);

    unsigned max_read = 65535;
    unsigned ln_cnt = 0;
    char linef1[max_read];
    char linef2[max_read];

    while(fgets(linef1, max_read, parameters.file1) != NULL &&
          fgets(linef2, max_read, parameters.file2) != NULL ){
        ln_cnt++;
        if(strcmp(linef1, linef2) != 0)
            break;
    }

    unsigned pos;
    for(pos = 0; linef1[pos] == linef2[pos]; pos++ ){
        ;
    }
    printf("%i: %s", ln_cnt, linef1);
    for(unsigned i=0; i<= pos; i++)
        printf(" ");
    printf("  ^\n");
    printf("%i: %s", ln_cnt, linef2);

    fclose(parameters.file1);
    fclose(parameters.file2);
    exit(0);
}

int parce_args(int argc, char **argv, struct parameters *parameters){
    if( argc < 3 ){
        fprintf(stderr,"Not enough arguments\n");
        exit(1);
    }
    argc--;
    argv++;
    if( (parameters->file1 = fopen(*argv, "r")) == NULL ){
        fprintf(stderr,"Can't open file '%s'\n", *argv);
        exit(1);
    }
    argc--;
    argv++;
    if( (parameters->file2 = fopen(*argv, "r")) == NULL ){
        fprintf(stderr,"Can't open file '%s'\n", *argv);
        exit(1);
    }
    return 0;
}
