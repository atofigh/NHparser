/*
 * Copyright (C) 2010, Ali Tofigh
 *
 * This file is part of NHparser, a library for parsing trees in the New
 * Hampshire or Newick format.
 *
 * NHparser is released under the terms of the license contained in the
 * file LICENSE.
 */

#ifndef NHGRAMMAR_H
#define NHGRAMMAR_H

#include <NHparser/NHtypes.h>

typedef struct desc_t {
    double      branchLength;
    char       *label;
} desc_t;

#endif
