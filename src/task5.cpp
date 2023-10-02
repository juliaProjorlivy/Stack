#include "stack_ctor_dtor.h"
#include "stack_error.h"
#include "stack_push_pop.h"
#include <limits.h>

int main()
{
    struct stack stk = {};
    int x = 0;

    STACK_CTOR(&stk, 2);
    for(int i = 0; i < INT_MAX; i++)
    {
        printf("hash %d\n", i);
       
        stack_push(&stk, i);
    }
    stk.data[stk.size++] = 89;
    for(int i = 0; i < 40; i++)
    {
        stack_pop(&stk, &x);
    }
    
    printf("%d\n", x);
    stack_dtor(&stk);
    return 0;
}