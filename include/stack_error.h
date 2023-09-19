#ifndef STACK_ERROR_H
#define STACK_ERROR_H

#define RED          "\x1b[31;1m" 
#define END_OF_COLOR "\x1b[39;49m"

#include "stack_ctor_dtor.h"

enum ERROR_CODE
{
    STK_PROBLEM,
    DATA_PROBLEM,
    SIZE_PROBLEM,
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
