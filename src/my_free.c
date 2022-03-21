#include <stdio.h>
#include "../include/my_secmalloc.h"
#include <sys/mman.h>
#include <string.h> // to remove after tests.

void my_free(void *ptr){
    printf("INFO: Calling free function...\n");
    if(ptr != NULL){
        int *pointer = ptr - sizeof(size_t); 
        int size = *pointer;
        int result = munmap(pointer,size);
        if(0 == result){
            printf("INFO: Successfully free %d bytes at %p",size - sizeof(size_t),ptr);
        }
    }else{
       printf("WARN: Performing free on NULL pointer"); 
    }
    
}
