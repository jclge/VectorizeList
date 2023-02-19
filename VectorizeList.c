/*
 ╔════════╦═══════════════════════╦════════╗
 ║        ║     VectorizeList     ║        ║
 ║   ___  ╚═══════════════════════╝  ___   ║
 ║  (o o)                           (o o)  ║
 ║ (  V  )  Julien Calenge © 2023  (  V  ) ║
 ╠═══m═m═════════════════════════════m═m═══╣
 ╠════ File name: VectorizeList.c          ║
 ╠═══ Description: C Binding to Vectorize  ║
 ╚═════════════════════════════════════════╝
 */

#include "VectorizeList.h"

struct node *last_node(struct node *head)
{
    struct node *temp = head;
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}

static void reverse(struct node **head_ref)
{
    struct node *prev = NULL;
    struct node *current = *head_ref;
    struct node *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

void setup_values(struct node *head, struct node *data)
{
    head->occ = data->occ;
    head->value = data->value;
}

struct node *setup_node(int value)
{
    struct node *head = malloc(sizeof(struct node));
    head->occ = value;
    head->next = NULL;
    return (head);
}

struct node *partition(struct node *first, struct node *last)
{
    struct node *pivot = first;
    struct node *front = first;
    struct node *data = setup_node(0);

    while (front != NULL && front != last) {
        if (front->occ < last->occ) {
            pivot = first;
            setup_values(data, first);
            setup_values(first, front);
            setup_values(first, data);
            first = first->next;
        }
        front = front->next;
    }
    setup_values(data, first);
    setup_values(first, last);
    setup_values(last, data);
    return pivot;
}

void quick_sort(struct node *first, struct node *last)
{
    if (first == last)
        return;

    struct node *pivot = partition(first, last);

    if (pivot != NULL && pivot->next != NULL)
        quick_sort(pivot->next, last);
    if (pivot != NULL && first != pivot)
        quick_sort(first, pivot);
}

void fill_linked_list(struct node **head, const char *value)
{
    struct node *current = *(head);

    for (;strcmp(value, current->value) != 0 && current->next != NULL; current = current->next);
    if (current->next == NULL && strcmp(value, current->value) != 0) {
        current->next = malloc(sizeof(struct node));
        current = current->next;
        current->value = value;
        current->occ = 1;
        current->next = NULL;
    } else {
        current->occ++;
    }
}

void free_list(struct node* head)
{
   struct node *tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

bool error_management(PyObject *args)
{
    if (PyTuple_Size(args) == 0) {
        PyErr_SetString(PyExc_ValueError, "Missing argument 'List'");
        return (0);
    }
    return (1);
}

struct objects *setup_env(PyObject *args, PyObject *kwargs)
{
    struct objects *env = malloc(sizeof(struct objects));
    const char *keywords[] = {"obj", "frequency", "reversed", NULL};
    env->frequency = 0;
    env->reversed = 0;
    env->my_list = PyList_New(0);

    PyArg_ParseTupleAndKeywords(args, kwargs, "O|ii", keywords, &env->obj, &env->frequency, &env->reversed);
    env->iter = PyObject_GetIter(env->obj);
    env->next = PyIter_Next(env->iter);
    env->head = malloc(sizeof(struct node));
    env->head->value = PyUnicode_AsUTF8(env->next);
    env->head->occ = 1;
    env->head->next = NULL;
    env->next = PyIter_Next(env->iter);
    return (env);
}

int iter_list(struct objects *env)
{
    const char *foo;
    int len = 0;

    while (true) {
        if (!env->next)
            break;
        foo = PyUnicode_AsUTF8(env->next);
        fill_linked_list(&env->head, foo);
        env->next = PyIter_Next(env->iter);
        len++;
    }
    return (len);
}

void resolve_keywords(struct objects *env)
{
    if (env->frequency)
        quick_sort(env->head, last_node(env->head));
    if (env->reversed)
        reverse(&env->head);
}

void fill_list(struct objects *env, int len)
{
    unsigned int k;
    struct node *tmp = env->head;

    env->iter = PyObject_GetIter(env->obj);
    env->next = PyIter_Next(env->iter);
    for (int j = 0; j != len + 1; j++) {
        for (k = 0; strcmp(PyUnicode_AsUTF8(env->next), tmp->value) != 0; tmp = tmp->next)
            k++;
        PyList_Append(env->my_list, PyLong_FromLong(k));
        env->next = PyIter_Next(env->iter);
        tmp = env->head;
    }
}

static PyObject *compute_list(PyObject *self, PyObject *args, PyObject *kwargs)
{
    if (error_management(args) == 0)
        return NULL;

    struct objects *env = setup_env(args, kwargs);
    int len = iter_list(env);
    PyObject *list;

    resolve_keywords(env);
    fill_list(env, len);
    free_list(env->head);
    list = env->my_list;
    free(env);
    return list;
}

static PyMethodDef myMethods[] = {
    { "compute_list", compute_list, METH_VARARGS | METH_KEYWORDS, "Takes a list of strings and transform it into integers" },
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef VectorizeList = {
    PyModuleDef_HEAD_INIT,
    "VectorizeList",
    "Vectorize column of dataset based of order of appearance.",
    -1,
    myMethods
};

PyMODINIT_FUNC PyInit_VectorizeList(void)
{
    return PyModule_Create(&VectorizeList);
}