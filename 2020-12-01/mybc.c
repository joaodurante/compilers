/**@<mybc.c::**/

#include <stdio.h>
#include <stdlib.h>
#include <tokens.h>

int getToken(FILE *source);
void E(void);

FILE *source;
int lookahead;

int main(int argc, char const *argv[]){
    source = fopen(argv[1], "r");
    if (argc == 1){
        source = stdin;
    }

    if (source == NULL){
        fprintf(stderr, "argv[1]: cannot open file... exiting\n", argv[1]);
        exit(-1);
    }

    lookahead = getToken(source);
    E();
    exit(0);
}