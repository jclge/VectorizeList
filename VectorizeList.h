/*
 ╔════════╦═══════════════════════╦════════╗
 ║        ║     VectorizeList     ║        ║
 ║   ___  ╚═══════════════════════╝  ___   ║
 ║  (o o)                           (o o)  ║
 ║ (  V  )  Julien Calenge © 2023  (  V  ) ║
 ╠═══m═m═════════════════════════════m═m═══╣
 ╠════ File name: VectorizeColumn.h        ║
 ╠═══ Description: C Header to Vectorize   ║
 ╚═════════════════════════════════════════╝
 */

#include <Python.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    const char *value;
    int occ;
    struct node *next;
} node;

typedef struct objects {
    struct node *head;
    PyObject *iter;
    PyObject *next;
    PyObject *obj;
    PyObject *my_list;
    int reversed;
    int frequency;
} objects;