#include "stack_push_pop.h"
#include "stack_error.h"
#include "stack_ctor_dtor.h"
#include "hash.h"
#include <limits.h>
#include <string.h>

int main()
{
    struct stack stk = {};
    int x = 0;

    STACK_CTOR(&stk, 2);
    for(int i = 0; i < 21; i++)
    {
        stack_push(&stk, i + 10);
    }
    for(int i = 0; i < 20; i++)
    {
        stack_pop(&stk, &x);
    }
    char *s1 = "abcdef";
    char *s2 = "abcdek";
    printf("hash data = %zu\n", oat_hash(stk.data, stk.capacity));
    
    printf("hash stk = %zu\n", oat_hash(&stk + canary_shift, data_size));
    printf("%d\n", x);
    stack_dtor(&stk);
    return 0;
}