#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdint.h>
#include "hash.h"

typedef uint32_t stack_result_t;

typedef int elem_t;

typedef uint64_t canary_t;

extern const size_t canary_size;

typedef uint32_t hash_t;

struct stack
{
    canary_t left_canary;
    elem_t *data;
    int size;
    int capacity;
    const char *file_name;
    const char *func_name;
    const char *arg_name;
    int line;
    canary_t right_canary;
    hash_t stk_hash;
    hash_t data_hash;
};

const size_t stk_size = sizeof(stack) - 2 * sizeof(hash_t);

#endif
