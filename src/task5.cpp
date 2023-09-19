#include <stdio.h>
#include "struct_stack.h"
#include "stack_error.h"

int main()
{
    struct stack stk = {};

    stack_ctor(&stk, 10);
    STACK_DUMP(&stk);
    return 0;
}