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
int isUINT(FILE *tape){
    int head;

    if (isdigit(head = getc(tape))){
        if (head != '0'){
            while (isdigit(head = getc(tape)));
            ungetc(head, tape);
        }
        return UINT;
    }
    ungetc(head, tape);
    return FALSE;    
}

/* Octal pattern is defined as
 * REGEX: 0[0-7]+
 */
int isOCT(FILE *tape) {
	int octPrefix = getc(tape);

	if(octPrefix == '0') {
		int next = getc(tape);

		if(next >= '0' && next <= '7') {
			while((next = getc(tape)) >= '0' && next <= '7');
			ungetc(next, tape);
			return OCT;
		} else {
			ungetc(next, tape);
			ungetc(octPrefix, tape);
		}
	}

	ungetc(octPrefix, tape);
	return 0;
}

/* Hexadecimal pattern is defined as
 * REGEX: 0[xX][0-9A-Fa-f]+
 */
int isHEX(FILE *tape) {
	int firstHexPrefix;

	if(firstHexPrefix = getc(tape) == '0') {
		int secondHexPrefix;

		if(secondHexPrefix = getc(tape) == 'x') {
			int head = getc(tape);

			if((head >= '0' && head <= '9') ||
			   (toupper(head) >= 'A' && toupper(head) <= 'F')) {
				   while((head=getc(tape) >= '0' && head <= '9') || (toupper(head) >= 'A' && toupper(head) <= 'F'));
				   ungetc(head, tape);
				   return HEX;
			}
			ungetc(head, tape);
		}
		ungetc(secondHexPrefix, tape);
	}
	ungetc(firstHexPrefix, tape);
	return 0;
}

int getToken(FILE *source){
    int token;

    skipspaces(source);
    if ((token = isID(source)))
		return token;
		
    else if ((token = isOCT(source)))
		return token;
    
    else if ((token = isHEX(source)))
		return token;
    
    else if ((token = isUINT(source)))
		return token;

    token = getc(source);
    return token;
}