/**@<mybc.c::**/

#include <stdio.h>
#include <stdlib.h>
#include <tokens.h>

int getToken(FILE *source);

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

    switch(lookahead){
        case ID:
            printf("o token identificado é ID\n");
            break;
        case UINT:
            printf("o token identificado é UINT\n");
            break;            
        default: 
            printf("token inválido\n");
    }

    exit(0);
}