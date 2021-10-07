#include "ex1.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>
#include <unistd.h>

void* aligned_malloc (unsigned int size, unsigned int align)
{
    /* Map the memory
                                               Unused
                       <----------------------------------------------------->
                          (1)               (2)              (3)       (4)     
                       |-------|-------------------------|--------|----------|
             ________________________________________________________________
            |          |       |    |     |  |           |        |          |
            |   Used   |       |    | 200 |  |           |        |          |
            |          |       |    |     |  |           |        |          |
            |__________|_______|____|_____|__|___________|________|__________|
                      /\           /\    /\
                      |            |     |
                    head    result[-1] result
                    (200)              (240)
    
    (1): The region to store the pointer to the first byte of the data we have 
    just allocated. It depend on the system (4 bytes for 32-bit machines and 8
    bytes for 64-bit machines) ~> sizeof(X*) bytes for this region
    X can be void, int, float, .... since sizeof(pointer) not depend on type!
    
    (2): The aligned region. We need only at most align - 1 bytes because it is
    the number of bytes at least such that it always exist M = [0, align - 1]
    such that the position of pointer after setoff is (sizeof(X*) + M) 
    divide by "align"
    
    (3): The allocated block memory. It store "size" byte
    
    (4): The remaining memory
    
    ~> The condition which the aligned allocated block memory success is the 
    remaining memory store >= 0 bytes. Or we have:
                malloc(sizeof(X*) + align - 1 + size) != NULL
                
    We have the pseudocode to do it:
    1. head <- malloc(sizeof(void*) + align - 1 + size)
    2. If (head == NULL) return NULL 
    // It mean the memory not enough to allocated
    3. result <- head + sizeof(void*) 
    4. while result < head + sizeof(void*) + align - 1
        4.1. If (result % align == 0) break;
        4.2. else result <- result + 1
    5. result[-1] <- head
    6. return result
    
    In step 3 and 4, we have some comment: We can do fast by 
    3. result <- head + sizeof(void*) + align - 1
    4. result <- getPointer(address = address(result) - address(result) % align)
    
        
    */
    void *head, *res; 
    if ((head = (void *) malloc(size + align + sizeof(void*))) == NULL)
        return NULL;
    size_t addr = (size_t) head + align + sizeof(void*);
    res = (void *)(addr - (addr % align));
    *((size_t*) res - 1) = (size_t) head;
    return res;
}

void* aligned_free(void *ptr)
{
    /* 
        By the above idea, it is easy to realize we only free the pointer head.
        So the function aligned_free it call thorugh parameter ptr which same 
        role of "res" in first function
        
        On the other head, since head = res[-1] so we only delete(res[-1])
    */
    free((void *)(*((size_t *)ptr - 1)));
}
