#include "stack_error.h"
#include <stdlib.h>

#define ELEM_PRINT_SPEC "%d"

uint32_t stack_errno = 0;

const int max_bit = 32;

const int poison = 0; ////////////!!!!!!!!!! change poison

const char *str_error[] =   {"memory allocation failure cannot access memory for struct stack", 
                                    "memory allocation failure cannot access memory for data",       
                                    "current position is out of range", 
                                    "size exceeds capacity",
                                    "free cells do not have poison inside",
                                    "canary detected invasion in the stack form the right",
                                    "canary detected invasion in the stack from the left",
                                    "canary detected invasion in the data from the right",
                                    "canary detected invasion in the data from the left"};

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
        fprintf(stderr, "   *[%d] = "ELEM_PRINT_SPEC";\n", i, stk->data[i]);
    }
    for(int i = stk->size; i < stk->capacity; i++)
    {
        fprintf(stderr, "   [%d] = "ELEM_PRINT_SPEC" (POISON);\n", i, stk->data[i]);
    }
    fprintf(stderr, "  }\n");
}

uint32_t stack_is_invalid(const struct stack *stk)
{
    uint32_t error = 0;

    if(!stk) 
    {
        error                                                       |= STK_PROBLEM;
        stack_errno = error;
        return error;
    }
    if(!stk->data) error                                            |= DATA_PROBLEM;
    if(stk->size < 0) error                                         |= SIZE_PROBLEM;
    if(stk->size > stk->capacity) error                             |= SIZE_OVER_CAPACITY_PROBLEM;
    for(int index = stk->size; index < stk->capacity; index++)
    {
        if(stk->data[index] != poison) error                        |= POISON_PROBLEM;
    }
    if(stk->right_canary != canary) error                           |= RIGHT_CANARY_STK_PROBLEM;
    printf("left_cnary_data = %lx\n", *(canary_t *)(stk->data - canary_shift));
    printf("right_cnary_data = %lx\n", *(canary_t *)(stk->data + stk->capacity));
    if(stk->left_canary != canary) error                            |= LEFT_CANARY_STK_PROBLEM;
    if(*((canary_t *)(stk->data - canary_shift)) != canary) error                 |= LEFT_CANARY_DATA_PROBLEM;
    if(*((canary_t *)(stk->data + stk->capacity)) != canary) error |= RIGHT_CANARY_DATA_PROBLEM;

    stack_errno = error;

    return error;
}
