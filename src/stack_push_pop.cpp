#include "stack_push_pop.h"
#include "stack_error.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

stack_result_t stack_realloc(struct stack *stk)
{
    if(stack_invalid(stk))
    {
        STACK_ERROR(stk, stack_errno);
        return stack_errno;
    }
    
    const int multiplier = 2;

    if(stk->size == stk->capacity)
    {
        stk->capacity *=multiplier;
        stk->data = (elem_t *)realloc(stk->data, (size_t)(stk->capacity)*(sizeof(elem_t)));

        memset(stk->data, INT_MIN, (size_t)(stk->capacity)*sizeof(elem_t));
    }

    else if((stk->size) * multiplier * multiplier == stk->capacity)
    {
        stk->capacity /=(multiplier*multiplier);
        stk->data = (elem_t *)realloc(stk->data, (size_t)(stk->capacity)*(sizeof(elem_t)));
    }

    return stack_errno;
}

stack_result_t stack_push(struct stack *stk, elem_t value)
{
    if(stack_invalid(stk))
    {
        STACK_ERROR(stk, stack_errno);
        return stack_errno;
    }
    
    stack_realloc(stk);

    stk->data[(stk->size)++] = value;

    return stack_errno;
}

stack_result_t stack_pop(struct stack *stk, elem_t *value)
{
    if(stack_invalid(stk))
    {
        STACK_ERROR(stk, stack_errno);
        return stack_errno;
    }
    if(stk->size == 0)
    {
        stack_errno = 0b0100;
        STACK_ERROR(stk, stack_errno);
        return stack_errno;
    }
    stk->size--;

    *value = stk->data[stk->size];

    stk->data[stk->size] = 0;

    stack_realloc(stk);

    return stack_errno;
}

