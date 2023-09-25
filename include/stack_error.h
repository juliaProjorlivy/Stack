#ifndef STACK_ERROR_H
#define STACK_ERROR_H

#define RED          "\x1b[31;1m" 
#define END_OF_COLOR "\x1b[39;49m"

#include "stack.h"
#include <limits.h>

const uint64_t canary = 0xCA11DED; 

const int poison = INT_MAX;

const size_t canary_shift = sizeof(canary_t)/sizeof(elem_t);

enum ERROR_CODE
{
    STK_PROBLEM                 = (1u << 0u),
    DATA_PROBLEM                = (1u << 1u),
    SIZE_PROBLEM                = (1u << 2u),
    SIZE_OVER_CAPACITY_PROBLEM  = (1u << 3u),
    POISON_PROBLEM              = (1u << 4u),
    RIGHT_CANARY_STK_PROBLEM    = (1u << 5u),
    LEFT_CANARY_STK_PROBLEM     = (1u << 6u),
    RIGHT_CANARY_DATA_PROBLEM   = (1u << 7u),
    LEFT_CANARY_DATA_PROBLEM    = (1u << 8u),
    HASH_STK_PROBLEM            = (1u << 9u),
    HASH_DATA_PROBLEM           = (1u << 10u),
};

extern stack_result_t stack_errno;

void stack_error_decode(uint32_t error);

void stack_dump(struct stack *stk, const char *file1, int line1, const char *func_name1, const char *arg_name1);

uint32_t stack_is_invalid(const struct stack *stk);

#define STACK_ERROR(stk, error) do                                                  \
                    {                                                               \
                        fprintf(stderr, RED"ERROR:");                               \
                        stack_error_decode((error));                                \
                        fprintf(stderr, END_OF_COLOR);                              \
                        stack_dump((stk), __FILE__, __LINE__, __func__, (#stk));    \
                    } while (0)


#endif
