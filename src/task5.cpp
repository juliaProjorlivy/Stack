#include "stack_ctor_dtor.h"
#include "stack_error.h"
#include "stack_push_pop.h"

int main()
{
    struct stack stk = {};
    int x = 0;

    STACK_CTOR(&stk, 2);
    for(int i = 0; i < 6; i++)
    {
        stack_push(&stk, i + 10);
    }
    for(int i = 0; i < 20; i++)
    {
        stack_pop(&stk, &x);
    }
    
    printf("%d\n", x);
    stack_dtor(&stk);
    return 0;
}