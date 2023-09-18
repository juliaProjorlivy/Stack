#include <stdio.h>
#include "struct_stack.h"

#define STACK_DUMP(stk) stack_dump((stk), __FILE__, __LINE__, __func__, (#stk))