#ifndef STRUCT_STACK_H
#define STRUCT_STACK_H

#include <stdio.h>
#include <stdint.h>

typedef uint32_t stack_result_t;

typedef int elem_t;

typedef uint64_t canary_t;

// const size_t n_canary = 2;

extern size_t canary_size;

struct stack
{
    uint64_t left_canary;
    elem_t *data;
    int size;
    int capacity;
    const char *file_name;
    const char *func_name;
    const char *arg_name;
    int line;
    uint64_t right_canary;
};

stack_result_t stack_ctor(struct stack *stk, int capacity, const char *file_name,
                                const char *func_name, const char *arg_name, int line);

stack_result_t stack_dtor(struct stack *stk);

#define STACK_CTOR(stk, capacity) stack_ctor((stk), (capacity), __FILE__, __func__, (#stk), __LINE__)

#endif
