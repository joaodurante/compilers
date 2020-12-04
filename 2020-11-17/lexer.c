/**@<lexer.c::**/
/**
 * This is the start project for the lexical analyser to be used
 * as the interface to the parser of the project mybc (my basic 
 * calculator)
 */
#include <stdio.h>
#include <ctype.h>
#include <tokens.h>

#define TRUE 1
#define FALSE 0

/**
 * In order to have a pattern scan we have first to implement a
 * method to ignore spaces
 * 
 */
void skipspaces(FILE *tape) {
    int head;

    while (isspace(head = getc(tape)));
    ungetc(head, tape);
}

/**
 * Now we need a predicate function to recognize a string
 * beginning with a letter (alpha) followed by zero or more
 * digits and letters
 * 
 * RegEx: [A-Za-z][A-Za-z0-9]*
 * isalpha(x) returns 1 if x in [A-Za-z]
 *            returns 0 otherwise  
 * isalnum(x) returns 1 if x in [A-Za-z0-9]
 *            returns 0 otherwise  
 */
int isID(FILE *tape){
    int head;
    
    if (isalpha(head = getc(tape))){
        while (isalnum(head = getc(tape)));
        ungetc(head, tape);
        return ID;
    }
    ungetc(head, tape);
    return FALSE;
}

/**
 * Next, we have to implement a method to recognize decimal
 * pattern (unsigned int)
 * 
 * RegEx: [1-9][0-9]* | 0
 */
int isUInt(FILE *tape){
    int head;

    if (isdigit(head = getc(tape))){
        if (head != '0'){
            while (isdigit(head = getc(tape)));
            ungetc(head, tape);
        }
        return U_INT;
    }
    ungetc(head, tape);
    return FALSE;    
}

int getToken(FILE *source){
    int token;

    skipspaces(source);
    if ( (token = isID(source)) ) return token;
    if ( (token = isUInt(source)) ) return token;

    token = getc(source);
    return token;
}