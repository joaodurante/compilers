/**@<parser.c::**/
/**
 * simplified recursive LL(1) parser for expressions 
 * 
 * LL(1)-gramar
 */
#include <parser.h>

/** 
 * E -> T R
 */
void E(void){
     T();
     R();
}

/**
 * R -> oplus T R  <>
 */
void R(void){
    if (lookahead == '+' || lookahead == '-') {
        match(lookahead); T(); R();
    } else {
        // reached this line because lookahead \in FOLLOW(R)
        // FOLLOW(R) = { EOF, ') }
        if(lookahead == EOF) {
            match(EOF);
        } else {
            ;
        }
    }
}

/**
 * T -> F Q
 */
void T(void){
    /* FOLLOW(T) = FIRST(R) - {<>} \cup FOLLOW(E)
     *           = {'+', '-', EOF, ')' } 
     */
    F();
    Q();
}

/**
 * Q -> otimes F Q  <>
 */
void Q(void){
    if (lookahead == '*' || lookahead == '/') {
         match(lookahead);
         F();
         Q();
    } else {
        // FOLLOW(Q) = {'+', '-', EOF, ')' }
        switch(lookahead) {
            case '+':
            case '-':
                break;
            case EOF:
                match(lookahead);
                break;
            default:
                ;
        }
    }
}

/**
 * F -> (E) | UINT | ID
 */
void F(void) { 
	switch (lookahead) {
		case '(':
			match('(');
			E();
			match(')');
			break;
		case UINT:
		case HEX:
		case OCT:
			match(lookahead);
			break;
		default:
			match(ID);
	}
}

void match(int expected){
    if (lookahead == expected){
        lookahead = getToken(source);
    } else {
        fprintf(stderr, "token mismatch: expected %d whereas found %d\n", expected, lookahead);
        exit(-2);
    }
}