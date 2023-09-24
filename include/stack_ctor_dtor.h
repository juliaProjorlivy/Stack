#ifndef STRUCT_STACK_H
#define STRUCT_STACK_H

#include "stack.h"

stack_result_t stack_ctor(struct stack *stk, int capacity, const char *file_name,
                                const char *func_name, const char *arg_name, int line);

stack_result_t stack_dtor(struct stack *stk);

#define STACK_CTOR(stk, capacity) stack_ctor((stk), (capacity), __FILE__, __func__, (#stk), __LINE__)

#endif
