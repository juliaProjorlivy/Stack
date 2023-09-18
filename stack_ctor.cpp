#include "struct_stack.h"
#include <stdlib.h>
#include <stdint.h>

#define SP_EL "%d"

void stack_dump(struct stack *stk, char *file1, int line1, char *func_name1, char *arg_name1,
                                    char *file2, int line2, char *func_name2)
{
    fprintf(stderr, "%s from %s (%d) %s\n", arg_name1, file1, line1, func_name1);
    fprintf(stderr, "called from %s (%d) %s\n{\n", file2, line2, func_name2);
    fprintf(stderr, "\t size = ;\n", stk->size);
    fprintf(stderr, "\t capacity = ;\n\t\t{\n", stk->capacity);
    for(int i = 0; i < stk->size; i++)
    {
        fprintf(stderr, "\t\t\t*[%d] = "SP_EL";\n", i, stk->data[i]);
    }
    for(int i = stk->size; i < stk->capacity; i++)
    {
        fprintf(stderr, "\t\t\t*[%d] = "SP_EL" (POISON);\n", i, stk->data[i]);
    }
    fprintf(stderr, "\t\t}\n}");
}

typedef struct
{
    uint32_t err1: 1;  // 1 bits of the byte
    uint32_t err2: 6;  // 6 more bits of the byte
} error;

uint32_t stack_verificator(const struct stack *stk)
{
    uint32_t error = 0;

    if(!stk) error |= 1;
    if(!stk->data) error |= 2;

    return error;
}

enum ERROR_NAME stack_ctor(struct stack *stk)
{
    stk->size = 0;
    stk->capacity = 10;
    (stk->data)[stk->capacity] = {};

    return
}



enum ERROR_NAME stack_dtor(struct stack *stk)
{
    free(stk->data);
}

enum ERROR_NAME stack_push(struct stack *stk, elem_t value)
{
    const int multiplier = 2;

    if(stk->size > stk->capacity)
    {
        stk->data = (elem_t *)realloc(stk->data, multiplier*(stk->capacity));
    }

    stk->data[stk->size++] = value;

    r
}