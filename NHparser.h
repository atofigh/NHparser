#ifndef NHPARSER_H
#define NHPARSER_H

#include <stdio.h>
#include "NHtypes.h"

NHNode *
NH_read_tree (FILE *inFile, FILE *errorFile, const char *errorPrefix);

void
NH_destroy_tree (NHNode *root);

int
NH_get_lineno ();

int
NH_get_colno ();

void
NH_set_lineno (int newLineno);

void
NH_set_colno (int newColno);

#endif
