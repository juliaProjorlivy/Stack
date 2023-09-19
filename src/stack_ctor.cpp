#include "struct_stack.h"
#include "stack_error.h"
#include <stdlib.h>
#include <stdint.h>

#define SP_EL "%d"

extern uint32_t stack_errno = 0;

void stack_error_decode(uint32_t error)
{
    switch (error)
    {
    case 0b0001:
        
        break;
    
    default:
        break;
    }
}


void stack_dump(struct stack *stk, const char *file1, int line1, const char *func_name1, const char *arg_name1)
{
    fprintf(stderr, "%s from %s:%d %s()\n", arg_name1, file1, line1, func_name1);
    fprintf(stderr, " size = %zu;\n", stk->size);
    fprintf(stderr, " capacity = %zu;\n  {\n", stk->capacity);
    for(int i = 0; i < stk->size; i++)
    {
        fprintf(stderr, "   *[%d] = "SP_EL";\n", i, stk->data[i]);
    }
    for(int i = stk->size; i < stk->capacity; i++)
    {
        fprintf(stderr, "   [%d] = "SP_EL" (POISON);\n", i, stk->data[i]);
    }
    fprintf(stderr, "  }\n}\n");
}



uint32_t stack_valid(const struct stack *stk)
{
    uint32_t error = 0;

    if(!stk) error       |= 0b0001;
    if(!stk->data) error |= 0b0010;

    stack_errno = error;

    return error;
}

stack_result_t stack_ctor(struct stack *stk, size_t capacity)
{
    puts("here");
    stk->size = 0;
    stk->capacity = capacity;
    stk->data = (elem_t *)calloc(capacity, sizeof(elem_t));

    if(!stack_valid(stk))
    {
        STACK_DUMP(stk);
    }
    return stack_errno;
}



stack_result_t stack_dtor(struct stack *stk)
{
    if(!stack_valid(stk))
    {
        STACK_DUMP(stk);
    }

    free(stk->data);

    return stack_errno;
}

elem_t *stack_realloc(struct stack *stk)
{
    const int multiplier = 2;

    if(stk->size == stk->capacity)
    {
        stk->data = (elem_t *)realloc(stk->data, multiplier*(stk->capacity));
    }
}

stack_result_t stack_push(struct stack *stk, elem_t value)
{
    if(!stack_valid(stk))
    {
        STACK_DUMP(stk);
    }
    
    stk->data[stk->size++] = value;

    return stack_errno;
}

stack_result_t stack_pop(struct stack *stk, elem_t *value)
{
    if(!stack_valid(stk))
    {
        STACK_DUMP(stk);
    }

    stk->size--;
    *value = stk->data[stk->size];

    return stack_errno;
}

