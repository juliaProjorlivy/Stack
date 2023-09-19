#include "stack_error.h"
#include <stdlib.h>

stack_result_t stack_ctor(struct stack *stk, int capacity)
{
    stk->size = 0;
    stk->capacity = capacity;
    stk->data = (elem_t *)calloc((size_t)capacity, sizeof(elem_t));

    if(stack_invalid(stk))
    {
        STACK_ERROR(stk, stack_errno);
    }
    return stack_errno;
}

stack_result_t stack_dtor(struct stack *stk)
{
    if(stack_invalid(stk))
    {
        STACK_ERROR(stk, stack_errno);
        return stack_errno;
    }

    free(stk->data);

    return stack_errno;
}
