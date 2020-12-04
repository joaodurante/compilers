/**@<parser.c::**/
/**
 * simplified recursive LL(1) parser for expressions 
 * 
 * LL(1)-gramar
 */
#include <parser.h>


void E(void){
    if(lookahead == '-')
        match('-');
    

    _T:

    _F:
    
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

    if(lookahead == '*' || lookahead == '/') {
        match(lookahead);
        goto _F;
    }

    if(lookahead == '+' || lookahead == '-') {
        match(lookahead);
        goto _T;
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