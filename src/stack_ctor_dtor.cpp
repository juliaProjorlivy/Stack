#include "stack_ctor_dtor.h"
#include "stack_error.h"
#include <stdlib.h>

extern uint32_t stack_errno;

stack_result_t stack_ctor(struct stack *stk, size_t capacity)
{
    stk->size = 0;
    stk->capacity = capacity;
    stk->data = (elem_t *)calloc(capacity, sizeof(elem_t));

    if(stack_invalid(stk))
    {
        stack_error_decode(stack_errno);
        STACK_DUMP(stk);
    }
    return stack_errno;
}

stack_result_t stack_dtor(struct stack *stk)
{
    if(stack_invalid(stk))
    {
        stack_error_decode(stack_errno);
        STACK_DUMP(stk);
    }

    free(stk->data);

    return stack_errno;
}
