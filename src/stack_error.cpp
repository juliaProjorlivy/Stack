#include "stack_error.h"

#define SP_EL "%d"

// extern uint32_t stack_errno;
uint32_t stack_errno = 0;

void stack_error_decode(uint32_t error)
{
    switch (error)
    {
    case 0b0001:
        fprintf(stderr, "ERROR: memory allocation failure cannot access memory for struct stack\n");
        break;
    case 0b0010:
        fprintf(stderr, "ERROR: memory allocation failure cannot access memory for stack\n");
        break;
    case 0b0011:
        fprintf(stderr, "ERROR: memory allocation failure cannot access memory for struct stack and stack\n");
        break;
    case 0b0100:
        fprintf(stderr, "ERROR: current position is out of range\n");
        break;
    case 0b0101:
        fprintf(stderr, "ERROR: memory allocation failure cannot access memory for struct stack\n \
                                                                            current position is out of range\n"); 
        break;
    case 0b0110:
        fprintf(stderr, "ERROR: memory allocation failure cannot access memory for stack\n \
                                                                            current position is out of range\n");
        break;
    case 0b0111:
        fprintf(stderr, "ERROR: memory allocation failure cannot access memory for struct stack and stack\n \
                                                                            current position is out of range\n");
        break;
    default:
        puts("undefined error\n");
        break;
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
    fprintf(stderr, "  }\n}\n");
}

uint32_t stack_invalid(const struct stack *stk)
{
    uint32_t error = 0;

    if(!stk) error              |= 0b0001;
    if(!stk->data) error        |= 0b0010;
    if(stk->size < 0) error     |= 0b0100;

    stack_errno = error;

    return error;
}
