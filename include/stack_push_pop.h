#ifndef STACK_PUSH_POP_H
#define STACK_PUSH_POP_H

#include "stack_ctor_dtor.h"

stack_result_t stack_push(struct stack *stk, elem_t value);

stack_result_t stack_pop(struct stack *stk, elem_t *value);

#endif
