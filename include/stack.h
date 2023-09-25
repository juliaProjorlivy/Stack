#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdint.h>
#include "hash.h"

typedef uint32_t stack_result_t;

typedef int elem_t;

typedef uint64_t canary_t;

extern const size_t canary_size;

const size_t stk_size = 3*sizeof(int) + 3*sizeof(const char *) + sizeof(elem_t *);

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
    hash_t stk_hash; // TODO move to the end
    hash_t data_hash;
    canary_t right_canary;
};

#endif
