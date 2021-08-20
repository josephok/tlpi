#ifndef MALLOC_H
#define MALLOC_H
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

typedef struct block
{
    // Length of block
    size_t len;
    // Memory pointer
    void *ptr;
    // next block
    struct block *next_block;
    // free to use
    bool is_free;
} Block;

void *my_malloc(size_t size);
void my_free(void *ptr);

#endif