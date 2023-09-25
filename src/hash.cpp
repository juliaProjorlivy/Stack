#include "hash.h"
#include <stack.h>

uint32_t oat_hash(const void *s, size_t len)
{
    const unsigned char *p = (const unsigned char *)s;

    uint32_t h = 0;

    while(len--) {
        h += *p++;
        h += (h << 10);
        h ^= (h >> 6);
    }

    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);

    return h;
}


