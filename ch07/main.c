/* 7-2
Implement malloc() and free(). */

// void *malloc(size_t size);
// void free(void *ptr);
// int brk(void *addr);
// void *sbrk(intptr_t increment);
#include "malloc.h"
void print_block();
extern Block *head;

int main(int argc, char const *argv[])
{
    for (size_t i = 0; i < 10; i++)
    {
        char *s = my_malloc(8);
        snprintf(s, 8, "abcdefg");
        printf("%s\n", s);
        my_free(s);
    }
    print_block();
}

void print_block()
{
    Block *p = head;
    while (p != NULL)
    {
        printf("block address: %p, block length: %zu, memory pointer: %p, next_block_ptr: %p, is_free: %d\n",
               p, p->len, p->ptr, p->next_block, p->is_free);
        p = p->next_block;
    }
}