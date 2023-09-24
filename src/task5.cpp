#include "stack_push_pop.h"
#include "stack_error.h"
#include "stack_ctor_dtor.h"
#include <limits.h>

int main()
{
    struct stack stk = {};
    int x = 0;
    // stack_ctor(&stk, 5);
    STACK_CTOR(&stk, 2);
    for(int i = 0; i < 21; i++)
    {
        stack_push(&stk, i + 10);
        // STACK_ERROR(&stk, 0);
    }
    for(int i = 0; i < 21; i++)
    {
        stack_pop(&stk, &x);
    }
    printf("adress = %p\n", &stk);

    // stack_pop(&stk, &x);
    // STACK_ERROR(&stk, 0);
    printf("%d\n", x);
    stack_dtor(&stk);
    return 0;
}