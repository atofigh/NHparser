%{
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "NHgrammar.h"
#include "NHgrammar.y.h"
#include "NHerror.h"

extern YYLTYPE NH_12123_lloc;
int NH_12123_colno;

static void 
update_colno ();

static int 
tab_inc (int colno);

static char *
strd(char *s);

int fileno (FILE *);
#define YY_USER_ACTION                                  \
        NH_12123_lloc.first_line = NH_12123_lineno;            \
        NH_12123_lloc.first_column = NH_12123_colno;           \
        NH_12123_colno += yyleng;
%}

%option noyywrap
%option prefix = "NH_12123_" 
%option yylineno

LABEL           [[:alpha:]][[:alnum:]\-\_/+#!%&?]*
FLOAT           [+-]?[0-9]+(\.[0-9]+)?(e[-+]?[0-9]+)?

%%

\(                      return '(';
\)                      return ')';
,                       return ',';
:                       return ':';
;                       return ';';
\"                      return '"';
\'                      return '\'';
\n                      NH_12123_colno = 0;
\t                      NH_12123_colno += tab_inc(NH_12123_colno);
[[:space:]]             
{LABEL}                 NH_12123_lval.str = strd(yytext); return LABEL;
{FLOAT}                 NH_12123_lval.str = strd(yytext); return FLOAT;
\[&&([^]])*\]           {
                            NH_12123_colno -= yyleng;
                            update_colno();
                            NH_12123_lval.str = strd(yytext);
                            return ANNOTATION;
                        }
\[([^]])*\]             NH_12123_colno -= yyleng; update_colno();
.                       {
                            NH_error(NH_12123_lineno, NH_12123_colno - 1,
                                     "Unrecognized token."); 
                            return ERROR_TOK;
                        }
%%

void
update_colno () {
    char *cp;
    for (cp = yytext; *cp; cp++) {
        switch (*cp){
        case '\n': NH_12123_colno = 0; break;
        case '\t': NH_12123_colno += tab_inc(NH_12123_colno); break;
        default: NH_12123_colno++;
        }
    }
}

int
tab_inc (int colno) {
    return 8 - colno % 8;
}

char *
strd (char *str) {
    char *newStr;

    if (str == NULL)
        return NULL;
    
    newStr = malloc((strlen(str) + 1) * sizeof(char));
    assert(newStr);
    return strcpy(newStr, str);
}

void
NH_flush_buffer () {
    YY_FLUSH_BUFFER;
}
