#ifndef STACK_ERROR_H
#define STACK_ERROR_H

#include <stdio.h>
#include <stdint.h>

#define STACK_DUMP(stk) stack_dump((stk), __FILE__, __LINE__, __func__, (#stk))

#define ERROR(error) stack_error_decode(error)

void stack_error_decode(uint32_t error);

void stack_dump(struct stack *stk, const char *file1, int line1, const char *func_name1, const char *arg_name1);

uint32_t stack_invalid(const struct stack *stk);

#endif
