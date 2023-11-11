#include "stack_ctor_dtor.h"
#include "stack_error.h"
#include "stack_push_pop.h"
#include <limits.h>

int main()
{
    struct stack stk = {};
    elem_t x = 0;

    STACK_CTOR(&stk, 2);
    for(int i = 0; i < 10; i++)
    {
        printf("hash %d\n", i);
       
        stack_push(&stk, i);
    }
    
    for(int i = 0; i < 5; i++)
    {
        stack_pop(&stk, &x);
    }
    
    printf(ELEM_PRINT_SPEC "\n", x);
    stack_dtor(&stk);
    return 0;
}