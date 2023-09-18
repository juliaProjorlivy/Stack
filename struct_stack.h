#ifndef STRUCT_STUCK_H
#define STRUCT_STUCK_H

#include <stdio.h>

typedef int elem_t;

struct stack
{
    elem_t *data;
    size_t size;
    size_t capacity;
};

enum ERROR_NAME
{
    STK_NULL,
    DATA_NULL,
    STK_DATA_NULL,
};

void stack_dump(struct stack *stk, char *line, int n_str, char *func_name);

#endif
