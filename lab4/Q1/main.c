#include "ex1.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    void *p = aligned_malloc(16, 64);
    printf ("The allocation return to pointer p have address = %p\n", p);
    aligned_free (p);
}
