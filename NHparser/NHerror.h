/*
 * Copyright (C) 2010, Ali Tofigh
 *
 * This file is part of NHparser, a library for parsing trees in the New
 * Hampshire or Newick format.
 *
 * NHparser is released under the terms of the license contained in the
 * file LICENSE.
 */

#ifndef NHERROR_H
#define NHERROR_H

#include <stdio.h>

void
NH_error (int lineno, int colno, const char *msg);

void
NH_error_no_numbers (const char *msg);

void
NH_error_set_prefix (const char *prefix);

void
NH_error_set_err_file (FILE *errFile);

#endif
