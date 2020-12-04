/**@<parser.h::**/

#include <stdio.h>
#include <stdlib.h>
#include <tokens.h>

extern FILE *source;
extern int lookahead;
int getToken(FILE *source);

void match(int expected);
void T(void);
void R(void);
void F(void);
void Q(void);