#include "HeapAllocator.h"

heapStruct Heap;

int main(){
    Heap.start=NULL;

    //Get memory (MMAP)
    //Heap allocate
    //Heap free

    //structure for the heap metadata 
    //Structure for heap chunks

    return 0;
}

void *newMalloc(size_t size){
    if (size <= 0){ return 0;} 

    heapChunk *current = Heap.start;
    heapChunk *prev = NULL;

    while (current){ // first fit algorithm
        if(current->size<=size && current->free == true){
            current->free = false;
            return (void*)(current +1);
        }

        prev = current;
        current = current->next;
    }
    //If there are no blocks available, then request new memory


    size_t totalSize = PAGE_SIZE + size;

    heapChunk *newChunk = mmap(NULL,size,PROT_WRITE|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1,0); 
    // mmap to allocate new chunk of memory size of the argument

    if (newChunk == MAP_FAILED){
        printf("Mmap error");
        return 0;
    }

    //adding the new chunk to the linked list
    newChunk->size=totalSize;
    newChunk->free=false;
    newChunk->next= NULL;

    if(prev != NULL){
        prev->next = newChunk;
    }

    else{
        Heap.start=newChunk;
    }


    return (void*)(newChunk+1);
}

int newFree(size_t item){

    return 0;
}