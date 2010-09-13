#include <stdio.h>
#include <stdlib.h>
#include "NHparser.h"

static void write_tree_r (NHNode *n, FILE *out);
static void write_tree (NHNode *root, char *file);

/* See in-code comment about NH_12123_debug. */
//extern int NH_12123_debug;

int
main (int argc, char *args[]) {
    FILE *in = NULL;
    NHNode *root = NULL;

    /*
     * Check correct invokation.
     */
    if (argc != 2) {
        fprintf(stderr, "Usage: NHtester <filename>\n");
        exit(EXIT_FAILURE);
    } 
    
    /*
     * Open file and report errors.
     */
    in = fopen(args[1], "r");
    if (!in) {
        fprintf(stderr, "Could not open file '%s'.\n", args[1]);
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    /*
     * To see debug output from lex and yacc set NH_12123_debug to
     * one. NOTE! This is only for internal maintenance.
     */
    //    NH_12123_debug = 1;

    /*
     * Read the tree file. In case of syntax errors NH_read_tree will
     * output error information on the provided error stream, and
     * return NULL.
     */
    root = NH_read_tree(in, stderr, args[1]);
    if (root == NULL) {
        fprintf(stderr, "Error reading tree file.\nAborting.\n");
        exit(EXIT_FAILURE);
    }

    /*
     * Here a correct tree must have been read. We will just output
     * the tree structure in NHX-format.
     */
    printf("I managed to parse the following tree:\n");
    write_tree(root, NULL);
    printf("\n\n");
    printf("I detected end of tree at line %d and column %d.\n",
           NH_get_lineno(), NH_get_colno());

    /*
     * Free used memory and close files.
     */
    NH_destroy_tree(root);
    root = NULL;
    fclose(in);
    
    return EXIT_SUCCESS;
}

void
write_tree_r (NHNode *n, FILE *out) {
    NHNodeList *l;
    
    if (n == NULL) {
        return;
    }

    if (n->children == NULL) {
        fprintf(out, "%s", n->label ? n->label : "");
        if (n->branchLength >= 0) {
            fprintf(out, ":%g", n->branchLength);
        }
        if (n->annotation) {
            fprintf(out, "%s", n->annotation->str);
        }
    } else {
        fprintf(out, "(");
        for (l = n->children; l; l = l->next) {
            write_tree_r(l->node, out);
            if (l->next)
                fprintf(out, ",");
        }
        fprintf(out, ")");
        if (n->label) 
            fprintf(out, "%s", n->label);
        if (n->branchLength >= 0) {
            fprintf(out, ":%g", n->branchLength);
        }
        if (n->annotation) {
            fprintf(out, "%s", n->annotation->str);
        }
    }
}

void
write_tree (NHNode *root, char *file) {
    FILE *out;

    out = file ? fopen(file, "w") : stdout;
    if (out == NULL) {
        fprintf(stderr, "The file %s could not be opened for writing\n", file);
    }
    
    if (root == NULL) {
        if (file) 
            fclose(out);
        return;
    }
    
    write_tree_r(root, out);
    fprintf(out, ";");
    if (file)
        fclose(out);
}
