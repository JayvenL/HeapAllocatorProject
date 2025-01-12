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

int newFree(void *item){

    if (!item){
    
    printf("Item cannot be free'd");
    return 1;
    }

    heapChunk * chunkToBeRem = (heapChunk*)item -1; // this will get the metadata of the block

    if(chunkToBeRem->free == true){
        printf("Ptr already free");
        return 0;
    }
    heapChunk* currentPrtCheck = Heap.start;
    bool pointerInHeap =false;

    while(currentPrtCheck){
        if(currentPrtCheck == chunkToBeRem){
            pointerInHeap = true;
        }
        currentPrtCheck = currentPrtCheck->next;
    }

    if(!pointerInHeap){
        printf("Pointer is not in the heap");
        return 0;
        
    }

    chunkToBeRem->free=true;

    //Coalescing free block to reduce fragmentation

    heapChunk *current = chunkToBeRem;

    while(current->next && current->next->free){
        current->size += BLOCK_SIZE + current->next->size;
        current->next = current->next->next;
    }

    return 0;
}