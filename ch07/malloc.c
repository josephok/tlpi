#include "malloc.h"

Block *head = NULL;
void *my_malloc(size_t size)
{
    Block *p = head;
    Block *prev;
    while (p != NULL)
    {
        if (p->is_free && p->len >= size)
        {
            p->is_free = false;
            return p->ptr;
        }
        prev = p;
        p = p->next_block;
    }

    void *new_ptr = sbrk(size);
    Block *new_block_ptr = sbrk(sizeof(Block));
    new_block_ptr->len = size;
    new_block_ptr->ptr = new_ptr;
    new_block_ptr->next_block = NULL;
    new_block_ptr->is_free = false;

    if (head == NULL)
    {
        head = new_block_ptr;
    }
    else
    {
        prev->next_block = new_block_ptr;
    }

    return new_ptr;
}

void my_free(void *ptr)
{
    assert(ptr != NULL);
    Block *p = head;
    while (p != NULL)
    {
        if (ptr == p->ptr && !p->is_free)
        {
            p->is_free = true;
            return;
        }
        p = p->next_block;
    }
}