#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdint.h>

typedef uint32_t stack_result_t;

typedef int elem_t;

typedef uint64_t canary_t;

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

#endif
