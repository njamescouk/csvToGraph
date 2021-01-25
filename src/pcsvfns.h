// pcsvfns.h
#ifndef have_pcsvfns
#define have_pcsvfns

extern int pcsvlineno;
#include <stdio.h>

/* C++ wants prototypes, you 'just know' the declarations */
int pcsvlex();
int pcsvparse();
void pcsverror (char *s);
extern char g_curToken[BUFSIZ]; // assign to this when lexing
                                     // declare in .y

void scanString(const char *s);

extern FILE *pcsvin, *pcsvout;
extern int pcsvdebug;

// #define pcsvDEBUG 1
#endif // have_pcsvfns
