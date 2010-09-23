%{
#include <config.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "NHgrammar-common.h"
#include "NHerror.h"

#define YYPARSE_PARAM root
    
    /* With YYMAXDEPTH set to 30000 we are able to parse trees with
       9999 leaves, even if the tree is given in the shape
       '(a1,(a2,(a3...' which is most memory intensive. Trees given in
       the form '(((...,a3),a2),a1)' never pose a memory exhaustion
       problem.*/
#define YYMAXDEPTH 30000

int 
NH_12123_lex();

void 
NH_12123_error (char *str);

static NHNode *
new_NHNode (NHNode             *parent,
            NHNodeList         *children,
            char               *label,
            double              branchLength,
            NHAnnotation       *annotation,
            int                 lineno,
            int                 colno);
 
static NHAnnotation *
new_NHAnnotation (char *str, int lineno, int colno);

static NHNodeList *
new_NHNodeList (NHNode *node, NHNodeList *next);

extern void
NH_flush_buffer ();

%}

%union {
    char               *str;
    NHNode             *node;
    NHNodeList         *list;
    NHAnnotation       *annotation;
    desc_t              desc;
    double              dbl;
}

%locations
%name-prefix="NH_12123_"
%verbose

%token <str>            LABEL
%token <str>            FLOAT
%token <str>            ANNOTATION
%token                  ERROR_TOK
%type <node>            tree
%type <node>            leaf
%type <list>            subtree_list
%type <desc>            description
%type <annotation>      extension
%type <str>             label
%type <dbl>             branch_length

%%

all:            '(' subtree_list ')' description extension endmarker {
                    NHNodeList *l;
                    NHNode *r = new_NHNode(NULL, $2, $4.label, $4.branchLength,
                                          $5, @1.first_line, @1.first_column);
                    for (l = $2; l; l = l->next) {
                        l->node->parent = r;
                    }
                    *(NHNode **)(root) = r;
                    NH_flush_buffer();
                    YYACCEPT;
                }
              | /* Empty */ {*(NHNode **)(root) = NULL; NH_flush_buffer(); YYACCEPT;}
              | error {
                    NH_error(@1.first_line, @1.first_column, "Parse error.");
                    YYABORT;
                }
              | '(' subtree_list endmarker {
                    NH_error(@3.first_line, @3.first_column,
                             "Missing right parenthesis.");
                    YYABORT;
                }
;

endmarker:      ';'
;

tree:           '(' subtree_list ')' description extension {
                    NHNodeList *l;
                    $$ = new_NHNode(NULL, $2, $4.label, $4.branchLength,
                                    $5, @1.first_line, @1.first_column);
                    for (l = $2; l; l = l->next) {
                        l->node->parent = $$;
                    }
                }
              | leaf
              | '(' subtree_list endmarker {
                    NH_error(@3.first_line, @3.first_column,
                             "Missing right parenthesis.");
                    YYABORT;
                }
;

subtree_list:   tree {$$ = new_NHNodeList($1, NULL);}
              | subtree_list ',' tree {
                    NHNodeList *l;
                    $$ = $1;
                    for (l = $$; l->next; l = l->next)
                        ;
                    l->next = new_NHNodeList($3, NULL);
              }
;

description:    /* EMPTY */ {$$.label = NULL; $$.branchLength = -1;}
              | label {} {$$.label = $1; $$.branchLength = -1;}
              | ':' branch_length {$$.label = NULL; $$.branchLength = $2;}
              | label ':' branch_length {$$.label = $1; $$.branchLength = $3;}
;

leaf:           description extension {
                    $$ = new_NHNode(NULL, NULL, $1.label, $1.branchLength, $2,
                                    @1.first_line, @1.first_column);
              }
;

extension:      /* EMPTY */ {$$ = NULL;}
              | ANNOTATION {
                  $$ = new_NHAnnotation($1, @1.first_line, @1.first_column);
              }
;

label:          LABEL
;

branch_length:  FLOAT {
                    /*
                     * Assuming $1 is not null and that it actually
                     * does represent a floating point number. We
                     * don't check here for the case when no
                     * conversion is made due to the string given to
                     * strtod is not a float. We have to make sure in
                     * the scanner that we really have a float.
                     */
                    errno = 0;
                    $$ = strtod($1, NULL);
                    if (errno) {
                        if ($$ == 0) {
                            NH_error(@1.first_line,
                                     @1.first_column,
                                     "Number is too small.");
                            YYABORT;
                        } else {
                            NH_error(@1.first_line,
                                     @1.first_column,
                                     "Number is too large.");
                            YYABORT;
                        }
                    } else {
                        free($1);
                    }
              }
;

%%

void
NH_12123_error (char *str) {
    //    NH_error_no_numbers(str);
}

NHNode *
new_NHNode(NHNode              *parent,
           NHNodeList          *children,
           char                *label,
           double               branchLength,
           NHAnnotation        *annotation,
           int                  lineno,
           int                  colno)
{
    NHNode *ret = malloc(sizeof (NHNode)); assert(ret);
    ret->parent = parent;
    ret->children = children;
    ret->label = label;
    ret->branchLength = branchLength;
    ret->annotation = annotation;
    ret->lineno = lineno;
    ret->colno = colno;
    return ret;
}

static NHAnnotation *
new_NHAnnotation (char *str, int lineno, int colno) {
    NHAnnotation *ret = malloc(sizeof (NHAnnotation)); assert(ret);
    ret->str = str;
    ret->lineno = lineno;
    ret->colno = colno;
    return ret;
}

NHNodeList *
new_NHNodeList (NHNode *node, NHNodeList *next) {
    NHNodeList *ret = malloc(sizeof (NHNodeList)); assert(ret);
    ret->node = node;
    ret->next = next;
    return ret;
}
