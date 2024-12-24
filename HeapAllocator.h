#ifndef HEAPALLOCATOR_H
#define HEAPALLOCATOR_H
#include <unistd.h>
#include <stdbool.h>

struct heapStruct{
    struct heapChumk *start; // keeps track of the beginnig of the heap.
};

struct heapChunk{
    
    uint32_t size;
    bool free; // boolean to see if a chunk if being used
    struct heapChunk *next; // linked list style
};


#endif