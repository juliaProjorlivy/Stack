#include <stdlib.h>
#include <string.h>
#include "stack_push_pop.h"
#include "stack_error.h"

const int multiplier = 2;
const int decrease_multiplier = 2;

enum REALLOC_DATA
{
    TO_DECREASE = 0,
    TO_INCREASE = 1,
};

stack_result_t stack_realloc(struct stack *stk, int to_increase)
{
    if(stack_is_invalid(stk))
    {
        STACK_ERROR(stk, stack_errno);
        return stack_errno;
    }

    if(to_increase)
    {
        elem_t *data = (elem_t *)realloc(stk->data - canary_shift, 
                        sizeof(char)*(((size_t)(stk->capacity * multiplier))*sizeof(elem_t) + canary_size));

        if(!data)
        {
            stack_errno |= DATA_PROBLEM;
            STACK_ERROR(stk, stack_errno);
            return stack_errno;
        }

        stk->capacity *=multiplier;
        *(data + canary_shift + stk->capacity) = canary;
        stk->data = data + canary_shift; 

        for(int i = stk->size; i < stk->capacity; i++)
        {
            stk->data[i] = poison;
        }
    }

    else
    {
        elem_t *data = (elem_t *)realloc(stk->data - canary_shift, 
        (sizeof(char))*((size_t)(stk->capacity/(multiplier*decrease_multiplier))*sizeof(elem_t) + canary_size));
        if(!data)
        {
            stack_errno |= DATA_PROBLEM;
            STACK_ERROR(stk, stack_errno);
            return stack_errno;
        }
        stk->capacity /=(multiplier*decrease_multiplier);
        stk->data = data + canary_shift;
        *(stk->data + stk->capacity) = canary;
    }

    return stack_errno;
}

stack_result_t stack_push(struct stack *stk, elem_t value)
{
    if(stack_is_invalid(stk))
    {
        STACK_ERROR(stk, stack_errno);
        return stack_errno;
    }
    
    if(stk->size >= stk->capacity)
    {
        if(stack_realloc(stk, TO_INCREASE))
        {
            STACK_ERROR(stk, stack_errno);
            return stack_errno;
        }
    }

    stk->data[(stk->size)++] = value;

    stk->stk_hash = oat_hash(stk, stk_size);
    stk->data_hash = oat_hash(stk->data, (size_t)stk->capacity*sizeof(elem_t));

    return stack_errno;
}

stack_result_t stack_pop(struct stack *stk, elem_t *value)
{
    if(stack_is_invalid(stk))
    {
        STACK_ERROR(stk, stack_errno);
        return stack_errno;
    }
    if(stk->size <= 0)
    {
        stack_errno = 0b0100;
        STACK_ERROR(stk, stack_errno);
        return stack_errno;
    }
    stk->size--;

    *value = stk->data[stk->size];

    stk->data[stk->size] = poison;

    stk->stk_hash = oat_hash(stk, stk_size);
    stk->data_hash = oat_hash(stk->data, (size_t)stk->capacity*sizeof(elem_t));

    if((stk->size) * multiplier * decrease_multiplier <= stk->capacity)
    {
        if(stack_realloc(stk, TO_DECREASE))
        {
            STACK_ERROR(stk, stack_errno);
            return stack_errno;
        }
    }

    stk->stk_hash = oat_hash(stk, stk_size);
    stk->data_hash = oat_hash(stk->data, (size_t)stk->capacity*sizeof(elem_t));

    return stack_errno;
}

