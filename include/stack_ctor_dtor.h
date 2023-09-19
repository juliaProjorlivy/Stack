#ifndef STRUCT_STACK_H
#define STRUCT_STACK_H

#include <stdio.h>
#include <stdint.h>

typedef uint32_t stack_result_t;

typedef int elem_t;

struct stack
{
    elem_t *data;
    size_t size;
    size_t capacity;
};

stack_result_t stack_ctor(struct stack *stk, size_t capacity);

stack_result_t stack_dtor(struct stack *stk);

#endif
