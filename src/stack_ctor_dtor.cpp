#include "stack_error.h"
#include "stack_ctor_dtor.h"
#include "stack.h"
#include <stdlib.h>

const size_t canary_size =  2*sizeof(canary_t);

stack_result_t stack_ctor(struct stack *stk, int capacity, const char *file_name,
                                const char *func_name, const char *arg_name, int line)
{

    stk->right_canary = canary;
    stk->left_canary = canary;
    stk->file_name = file_name;
    stk->func_name = func_name;
    stk->arg_name = arg_name;
    stk->line = line;
    stk->size = 0;
    stk->capacity = capacity;

    elem_t *data = (elem_t *)calloc((size_t)(capacity*sizeof(elem_t) + canary_size), sizeof(char));
    if(!data)
    {
        //!!!!!!!!!!!!!!!!!!!
        stack_errno |= DATA_PROBLEM;
        STACK_ERROR(stk, stack_errno);
        return stack_errno;
    }
    *data = canary;
    stk->data = data + canary_shift;

    for(size_t i = 0; i < stk->capacity; i++)
    {
        stk->data[i] = poison;
    }

    *(data + capacity + canary_shift) = canary;

    stk->stk_hash = oat_hash(stk, stk_size);
    stk->data_hash = oat_hash(stk->data, (size_t)stk->capacity);

    if(stack_is_invalid(stk))
    {
        STACK_ERROR(stk, stack_errno);
        return stack_errno;
    }

    return stack_errno;
}

stack_result_t stack_dtor(struct stack *stk)
{
    if(stack_is_invalid(stk))
    {
        STACK_ERROR(stk, stack_errno);
        return stack_errno;
    }

    stk->data -= canary_shift;

    for(size_t i = 0; i < stk->capacity + canary_shift * 2; i++)
    {
        stk->data[i] = poison;
    }

    free(stk->data);

    return stack_errno;
}
