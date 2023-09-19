#include "stack_error.h"
#include <stdlib.h>

#define SP_EL "%d"

uint32_t stack_errno = 0;

const int max_bit = 32;

const char *str_error[] =   {"memory allocation failure cannot access memory for struct stack", 
                                    "memory allocation failure cannot access memory for stack",       
                                                            "current position is out of range"};

void stack_error_decode(uint32_t error)
{
    for(int shift = 0; shift < max_bit; shift++)
    {
        if((1 << shift) & error) fprintf(stderr, "%s\n", str_error[shift]);
    }   
}

void stack_dump(struct stack *stk, const char *file1, int line1, const char *func_name1, const char *arg_name1)
{
    fprintf(stderr, "%s from %s:%d %s()\n", arg_name1, file1, line1, func_name1);
    fprintf(stderr, " size = %d;\n", stk->size);
    fprintf(stderr, " capacity = %d;\n  {\n", stk->capacity);
    for(int i = 0; i < stk->size; i++)
    {
        fprintf(stderr, "   *[%d] = "SP_EL";\n", i, stk->data[i]);
    }
    for(int i = stk->size; i < stk->capacity; i++)
    {
        fprintf(stderr, "   [%d] = "SP_EL" (POISON);\n", i, stk->data[i]);
    }
    fprintf(stderr, "  }\n");
}

uint32_t stack_is_invalid(const struct stack *stk)
{
    uint32_t error = 0;

    if(!stk) 
    {
        error                   |= STK_PROBLEM;
        exit(EXIT_FAILURE);
    }
    if(!stk->data) error        |= DATA_PROBLEM;
    if(stk->size < 0) error     |= SIZE_PROBLEM;

    stack_errno = error;

    return error;
}
