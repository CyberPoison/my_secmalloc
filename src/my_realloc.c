#include <stdio.h>
#include "../include/my_secmalloc.h"
#include <sys/mman.h>
#include <string.h> // to remove after tests.

void *my_realloc(void *ptr, size_t size){

    printf("INFO: Calling function realloc...\n");

    if(ptr == NULL){
        return my_malloc(size);
    }
    if(size == 0){
        my_free(ptr);
        return NULL;
    }

    int *pointer = ptr - sizeof(size_t); 
    int old_size = *pointer - sizeof(size_t);
    *pointer = size + sizeof(size_t);
    if(size > old_size){
        printf("WARN: size provided bigger than old size, can't reallocate\n");
    }
    printf("INFO: Successfully reallocate %d bytes at %p \n",size,ptr);
    return ptr;
}
