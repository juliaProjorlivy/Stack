#include "stack_push_pop.h"
#include "stack_error.h"
#include <limits.h>

int main()
{
    struct stack stk = {};
    int x = 0;
    stack_ctor(&stk, 5);
    for(int i = 0; i < 7; i++)
    {
        stack_push(&stk, i);
    }
    for(int i = 0; i < 9; i++)
    {
        stack_pop(&stk, &x);
    }

    stack_pop(&stk, &x);
    // printf("code = %d\n", (int)(char)INT_MIN);
    printf("%d\n", x);
    stack_dtor(&stk);
    return 0;
}