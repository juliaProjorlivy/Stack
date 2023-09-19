#include "stack_error.h"
#include <stdlib.h>

stack_result_t stack_ctor(struct stack *stk, int capacity)
{
    stk->size = 0;
    stk->capacity = capacity;
    elem_t *data = (elem_t *)calloc((size_t)capacity, sizeof(elem_t));
    if(!data)
    {
        //!!!!!!!!!!!!!!!!!!!
        stack_errno |= DATA_PROBLEM;
        STACK_ERROR(stk, stack_errno);
        exit(EXIT_FAILURE);
    }
    stk->data = data;

    if(stack_is_invalid(stk))
    {
        STACK_ERROR(stk, stack_errno);
        exit(EXIT_FAILURE);
    }
    return stack_errno;
}

stack_result_t stack_dtor(struct stack *stk)
{
    if(stack_is_invalid(stk))
    {
        STACK_ERROR(stk, stack_errno);
        exit(EXIT_FAILURE);
    }

    free(stk->data);

    return stack_errno;
}
