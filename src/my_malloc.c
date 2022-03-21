#include <stdio.h>
#include "../include/my_secmalloc.h"
#include <sys/mman.h>
#include <string.h> // to remove after tests.

// printf = log to put in file later

void *my_malloc(size_t size){
    printf("INFO: Calling malloc function...\n");
    if(size == 0){
        printf("WARN: allocating 0 bytes returning NULL pointer\n"); 
        return NULL;
    }
    int *pointer = mmap(NULL,sizeof(size_t)+size,PROT_READ | PROT_WRITE | PROT_EXEC,MAP_PRIVATE | MAP_ANONYMOUS,-1,0);
    if(pointer == MAP_FAILED){
        printf("ERROR: Mapping Failed\n");  
    }
    else{
       
        int *ptr = pointer;
        pointer += sizeof(size_t)/sizeof(int); // 8/4 = 2
        *ptr = size + sizeof(size_t);
        printf("INFO: Successfully Allocate %d bytes at %p\n",size,pointeur);
    }
    
    return pointer;
}
