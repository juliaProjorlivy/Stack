#include "stack_push_pop.h"
#include "stack_error.h"
#include <stdlib.h>
#include <string.h>

stack_result_t stack_realloc(struct stack *stk)
{
    if(stack_is_invalid(stk))
    {
        STACK_ERROR(stk, stack_errno);
        exit(EXIT_FAILURE);
    }
    
    const int multiplier = 2;
    const int decrease_multiplier = 2;

    if(stk->size >= stk->capacity)
    {
        stk->capacity *=multiplier;
        elem_t *data = (elem_t *)realloc(stk->data, (size_t)(stk->capacity)*(sizeof(elem_t)));
        if(!data)
        {
            //!!!!!!!!!!!!!!!!!!!!!!!!!!
            stack_errno |= DATA_PROBLEM;
            STACK_ERROR(stk, stack_errno);
            exit(EXIT_FAILURE);
        }
        stk->data = data;
        memset(stk->data + stk->size, '0', sizeof(elem_t)*(size_t)(stk->capacity - stk->size));
    }

    else if((stk->size) * multiplier * decrease_multiplier == stk->capacity)
    {
        stk->capacity /=(multiplier*decrease_multiplier);
        elem_t *data = (elem_t *)realloc(stk->data, (size_t)(stk->capacity)*(sizeof(elem_t)));
        if(!data)
        {
            //!!!!!!!!!!!!!!!!!!!!!!!!!!
            stack_errno |= DATA_PROBLEM;
            STACK_ERROR(stk, stack_errno);
            exit(EXIT_FAILURE);
        }
        stk->data = data;
    }

    return stack_errno;
}

stack_result_t stack_push(struct stack *stk, elem_t value)
{
    if(stack_is_invalid(stk))
    {
        STACK_ERROR(stk, stack_errno);
        exit(EXIT_FAILURE);
    }
    
    if(stack_realloc(stk))
    {
        STACK_ERROR(stk, stack_errno);
        exit(EXIT_FAILURE);
    }

    stk->data[(stk->size)++] = value;

    return stack_errno;
}

stack_result_t stack_pop(struct stack *stk, elem_t *value)
{
    if(stack_is_invalid(stk))
    {
        STACK_ERROR(stk, stack_errno);
        exit(EXIT_FAILURE);
    }
    if(stk->size <= 0)
    {
        stack_errno = 0b0100;
        STACK_ERROR(stk, stack_errno);
        exit(EXIT_FAILURE);
    }
    stk->size--;

    *value = stk->data[stk->size];

    stk->data[stk->size] = 0;

    if(stack_realloc(stk))
    {
        STACK_ERROR(stk, stack_errno);
        exit(EXIT_FAILURE);
    }

    return stack_errno;
}

