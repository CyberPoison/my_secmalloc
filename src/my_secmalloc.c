#include <stdio.h>
#include "../include/my_secmalloc.h"
#include <sys/mman.h>
#include <string.h> // to remove after tests.

void *my_malloc(size_t size){
    printf("INFO: Calling malloc function...\n");
    if(size == 0){
        printf("WARN: allocating 0 bytes returning NULL pointer\n"); 
        return NULL;
    }
    int *pointer = mmap(NULL,sizeof(size_t)+size,PROT_READ | PROT_WRITE | PROT_EXEC,MAP_PRIVATE | MAP_ANONYMOUS,-1,0);
    if(pointer == MAP_FAILED) {
        printf("ERROR: Mapping Failed\n");  
    }
    else {
        int *ptr = pointer;
        pointer += sizeof(size_t)/sizeof(int); // 8/4 = 2
        *ptr = size + sizeof(size_t);
        printf("INFO: Successfully Allocate %ld bytes at %p\n",size,pointer);
    }
    
    return pointer;
}


void my_free(void *ptr){
    printf("INFO: Calling free function...\n");
    if(ptr != NULL){
        int *pointer = ptr - sizeof(size_t); 
        int size = *pointer;
        int result = munmap(pointer,size);
        if(0 == result){
            printf("INFO: Successfully free %ld bytes at %p",size - sizeof(size_t),ptr);
        }
    }else{
       printf("WARN: Performing free on NULL pointer"); 
    }
}

void *my_calloc(size_t nmemb, size_t size){

    printf("INFO: Calling function calloc...\n");
    size_t max_size = nmemb * size;
    int *ptr = my_malloc(max_size);
    int *cp_ptr = ptr;

    printf("BEFORE %p\n",ptr);
    if(ptr != MAP_FAILED){
        for(int i = 0;i<max_size;i++){
            cp_ptr += 1;
            *cp_ptr = 0;
            printf("%d",*cp_ptr);
        }
        printf("AFTER %p\n",ptr);
    }

    return ptr;
}

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
    printf("INFO: Successfully reallocate %ld bytes at %p \n",size,ptr);
    return ptr;
}
