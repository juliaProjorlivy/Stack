#ifndef STACK_ERROR_H
#define STACK_ERROR_H

#include <stdio.h>
#include <stdint.h>
// #include "struct_stack.h"

#define STACK_DUMP(stk) stack_dump((stk), __FILE__, __LINE__, __func__, (#stk))

#define ERROR(error) stack_error_decode(error)

void stack_error_decode(uint32_t error);

#endif
