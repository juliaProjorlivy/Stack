#ifndef STACK_HASH_H
#define STACK_HASH_H

#include <stdint.h>
#include <stdio.h>

uint32_t oat_hash(const void *s, size_t len);

uint32_t ooat_hash(int *p, size_t len);

#endif
