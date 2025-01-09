#ifndef HEAPALLOCATOR_H
#define HEAPALLOCATOR_H
#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <stdio.h>

#define BLOCK_SIZE sizeof(heapChunk)
#define PAGE_SIZE 4096 // 4kB



typedef struct heapStruct{
    struct heapChunk *start; // keeps track of the beginnig of the heap.
}heapStruct;

typedef struct heapChunk{
    uint32_t size;
    bool free; // boolean to see if a chunk if being used
    struct heapChunk *next; // linked list style
}heapChunk;


int *newMalloc(size_t item);
int newFree(void *item);



#endif