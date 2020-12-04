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
     T(); R();
}

/**
 * R -> oplus T R  <>
 */
void R(void){
    if (lookahead == '+' || lookahead == '-') {
        match(lookahead); T(); R();
    }
}

/**
 * T -> F Q
 */
void T(void){
    F(); Q();
}

/**
 * Q -> otimes F Q  <>
 */
void Q(void){
    if (lookahead == '*' || lookahead == '/') {
         match(lookahead); F(); Q();
    }
}

/**
 * F -> (E) | U_INT | ID
 */
void F(void){
    switch(lookahead){
        case '(':
            match('('); E(); match(')');
            break;
        case U_INT:
            match(U_INT);
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