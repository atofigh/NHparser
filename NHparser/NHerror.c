#include <stdio.h>
#include "NHerror.h"

static const char *errorPrefix;
static FILE *err;

void
NH_error (int lineno, int colno, const char *msg) {
    if (err == NULL) {
        return;
    }
    if (errorPrefix != NULL && *errorPrefix != '\0') {
        fprintf(err, "%s:%d:%d: ", errorPrefix, lineno, colno);
    }
    fprintf(err, "%s\n", msg);
}

void
NH_error_no_numbers (const char *msg) {
    if (err == NULL) {
        return;
    }
    if (errorPrefix != NULL && *errorPrefix != '\0') {
        fprintf(err, "%s: ", errorPrefix);
    }
    fprintf(err, "%s\n", msg);
}

void
NH_error_set_prefix (const char *prefix) {
    errorPrefix = prefix;
}

void
NH_error_set_err_file (FILE *errFile) {
    err = errFile;
}

