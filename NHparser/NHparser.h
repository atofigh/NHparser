/*
 * Copyright (C) 2010, Ali Tofigh
 *
 * This file is part of NHparser, a library for parsing trees in the New
 * Hampshire or Newick format.
 *
 * NHparser is released under the terms of the license contained in the
 * file LICENSE.
 */

#ifndef NHPARSER_NHPARSER_H
#define NHPARSER_NHPARSER_H

#include <stdio.h>
#include <NHparser/NHtypes.h>

#ifdef __cplusplus
extern "C" {
#endif

NHNode *
NH_read_tree (FILE *inFile, FILE *errorFile, const char *errorPrefix);

NHNode *
NH_read_tree_str (const char *str, FILE *errorFile, const char *errorPrefix);

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

#ifdef __cplusplus
}
#endif

#endif
