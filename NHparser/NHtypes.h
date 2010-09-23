#ifndef NHPARSER_NHTYPES_H
#define NHPARSER_NHTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

struct NHNodeList;

struct NHAnnotation;

typedef struct NHNode {
    struct NHNode              *parent;
    struct NHNodeList          *children;
    char                       *label;
    double                      branchLength;
    struct NHAnnotation        *annotation;
    int                         lineno;
    int                         colno;
} NHNode;

typedef struct NHAnnotation {
    char                       *str;
    int                         lineno;
    int                         colno;
} NHAnnotation;

typedef struct NHNodeList {
    struct NHNode              *node;
    struct NHNodeList          *next;
} NHNodeList;

#ifdef __cplusplus
}
#endif

#endif
