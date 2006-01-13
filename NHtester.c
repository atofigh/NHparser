#include <stdio.h>
#include <stdlib.h>
#include "NHparser.h"

static void
write_tree_r (NHNode *n, FILE *out);

static void
write_tree (NHNode *root, char *file);

extern int NH_12123_debug;

int
main (int argc, char *args[]) {
    NHNode *root;
    FILE *in, *err;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s tree-file\n", args[0]);
        exit(1);
    } 
    
    in = fopen(args[1], "r");
    err = stderr;

    NH_12123_debug = 1;
    root = NH_read_tree(in, err, args[1]);
    write_tree(root, NULL);
    printf("\n");
    //    printf("%d, %d\n", NH_get_lineno(), NH_get_colno());
    return 0;
}

void
write_tree_r (NHNode *n, FILE *out) {
    NHNodeList *l;
    
    if (n == NULL) {
        return;
    }

    if (n->children == NULL) {
        fprintf(out, "%s", n->label);
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
