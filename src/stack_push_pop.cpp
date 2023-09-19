#include "stack_push_pop.h"
#include "stack_error.h"
#include <stdlib.h>

static void stack_realloc(struct stack *stk)
{
    const int multiplier = 2;

    if(stk->size == stk->capacity)
    {
        stk->capacity *=multiplier;
        stk->data = (elem_t *)realloc(stk->data, (size_t)(stk->capacity));
    }

    else if((stk->size) * multiplier * multiplier <= stk->capacity)
    {
        stk->capacity /=(multiplier*multiplier);
        stk->data = (elem_t *)realloc(stk->data, (size_t)(stk->capacity));
    }
}

stack_result_t stack_push(struct stack *stk, elem_t value)
{
    if(stack_invalid(stk))
    {
        ERROR(stack_errno);
        STACK_DUMP(stk);
    }

    stack_realloc(stk);

    stk->data[stk->size++] = value;

    return stack_errno;
}

stack_result_t stack_pop(struct stack *stk, elem_t *value)
{
    if(stack_invalid(stk))
    {
        ERROR(stack_errno);
        STACK_DUMP(stk);
    }

    stack_realloc(stk);

    stk->size--;
    *value = stk->data[stk->size--];

    return stack_errno;
}

