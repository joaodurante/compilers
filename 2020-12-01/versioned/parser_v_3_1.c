/**@<parser.c::**/
/**
 * simplified recursive LL(1) parser for expressions 
 * 
 * LL(1)-gramar
 */
#include <parser.h>

/** 
 * E -> T { oplus T }
 */
void E(void){
    if(lookahead == '-')
        match('-');
    

    _T: 
    T();
    if(lookahead == '+' || lookahead == '-') {
        match(lookahead);
        goto _T;
    }
}

/**
 * T -> F { Fotimes F}
 */
void T(void){
    /* FOLLOW(T) = FIRST(R) - {<>} \cup FOLLOW(E)
     *           = {'+', '-', EOF, ')' } 
     */
    _F:
    F();
    if(lookahead == '*' || lookahead == '/') {
        match(lookahead);
        goto _F;
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