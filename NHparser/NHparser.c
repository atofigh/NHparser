#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <NHparser/NHparser.h>
#include "NHerror.h"

extern FILE *NH_12123_in;
extern int NH_12123_colno;
extern int NH_12123_lineno;

extern void
NH_12123_read_string (const char *str);

extern void
NH_12123_delete_string_buffer ();

extern int
NH_12123_parse();

int
NH_get_lineno () {
    return NH_12123_lineno;
}

int
NH_get_colno () {
    return NH_12123_colno;
}

void
NH_set_lineno (int newLineno) {
    NH_12123_lineno = newLineno;
}

void
NH_set_colno (int newColno) {
    NH_12123_colno = newColno;
}

NHNode *
NH_read_tree_str (const char *str, FILE *errorFile, const char *errorPrefix)
{
    int c;
    int oldErrno;
    NHNode *root;

    if (str == NULL) {
        return NULL;
    }

    NH_error_set_err_file(errorFile);
    NH_error_set_prefix(errorPrefix);
    NH_12123_in = NULL;
    NH_12123_read_string(str);

    if (NH_12123_parse((void *) &root)) {
        NH_12123_delete_string_buffer();
        return NULL;
    }
    NH_12123_delete_string_buffer();
    return root;
}


NHNode *
NH_read_tree (FILE *inFile, FILE *errorFile, const char *errorPrefix){
    int c;
    int oldErrno;
    NHNode *root;

    if (inFile == NULL) {
        return NULL;
    }

    oldErrno = errno;
    errno = 0;
    c = fgetc(inFile);
    if (c == EOF) {
        if (errno && errorFile) {
            fprintf(errorFile, "NH_read_tree(): Fatal error.\n"
                    "NH_read_tree: %s\n", strerror(errno));
        }
        errno = oldErrno;
        return NULL;
    }
    ungetc(c, inFile);
    errno = oldErrno;

    NH_error_set_err_file(errorFile);
    NH_error_set_prefix(errorPrefix);
    NH_12123_in = inFile;

    if (NH_12123_parse((void *) &root)) {
        return NULL;
    }
    return root;
}

static void
NH_destroy_list (NHNodeList *list);

void
NH_destroy_tree (NHNode *root) {
    NHNodeList *list;

    if (root == NULL)
        return;

    for (list = root->children; list; list = list->next) {
        NH_destroy_tree(list->node);
    }
    free(root->label);
    if (root->annotation) {
        free(root->annotation->str);
        free(root->annotation);
    }
    NH_destroy_list(root->children);
    free(root);

    return;
}

static void
NH_destroy_list (NHNodeList *list) {
    if (list == NULL)
        return;

    NH_destroy_list(list->next);
    free(list);
    return;
}
