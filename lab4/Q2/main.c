#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    void *cur_brk, *tmp_brk = NULL;
    printf("My pid = %d\n", getpid());
    tmp_brk = cur_brk = sbrk(0);
    printf("Program Break Location 1 = %p\n", cur_brk);
    
    brk(cur_brk + 4096);
    cur_brk = sbrk(0);
    printf("Program Break Location 2 = %p\n", cur_brk);
    
    brk(tmp_brk);
    cur_brk = sbrk(0);
    printf("Program Break Location 3 = %p\n", cur_brk);
    
    sbrk(4096);
    cur_brk = sbrk(0);
    printf("Program Break Location 4 = %p\n", cur_brk);
    
    sbrk(-4096);
    cur_brk = sbrk(0);
    printf("Program Break Location 5 = %p\n", cur_brk);
    return 0;
}
