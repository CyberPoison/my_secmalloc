#include <stdio.h>
#include "../include/my_secmalloc.h"
#include <sys/mman.h>
#include <string.h>



void *my_malloc(size_t size) {
    FILE *fd; 
    fd = fopen ("data.log", "w");
    fprintf(fd, "INFO: Calling malloc function...\n");
    
    if (size == 0){
        fprintf(fd, "WARN: allocating 0 bytes returning NULL pointer\n"); 
        return NULL;
    }
    int *pointer = mmap(NULL,sizeof(size_t)+size,PROT_READ | PROT_WRITE | PROT_EXEC,MAP_PRIVATE | MAP_ANONYMOUS,-1,0);
    if (pointer == MAP_FAILED) {
        fprintf(fd, "ERROR: Mapping Failed\n");  
    }
    else {
        pointer += sizeof(size_t)/sizeof(int);
        fprintf(fd, "INFO: Successfully Allocate %ld bytes at %p\n",size,pointer);
    } 
    return pointer;
}


void my_free(void *ptr) {
    FILE *fd; 
    fd = fopen ("data.log", "w"); 
    fprintf(fd, "INFO: Calling free function...\n");
    
    if (ptr != NULL){
        int *pointer = ptr - sizeof(size_t); 
        int size = *pointer;
        int result = munmap(pointer,size);
        if(0 == result){
            fprintf(fd, "INFO: Successfully free %ld bytes at %p",size - sizeof(size_t),ptr);
        }
    } else {
        fprintf(fd, "WARN: Performing free on NULL pointer"); 
    }
}

void *my_calloc(size_t nmemb, size_t size) {
    FILE *fd; 
    fd = fopen ("data.log", "w");
    fprintf(fd, "INFO: Calling function calloc...\n");
    
    size_t max_size = nmemb * size;
    int *ptr = my_malloc(max_size);
    int *cp_ptr = ptr;
    fprintf(fd, "BEFORE %p\n",ptr);
    
    if( ptr != MAP_FAILED) {
        for(int i = 0;i<max_size;i++){
            cp_ptr += 1;
            *cp_ptr = 0;
            fprintf(fd, "%d",*cp_ptr);
        }
        fprintf(fd, "AFTER %p\n",ptr);
    }
    return ptr;
}

void *my_realloc(void *ptr, size_t size) {
    FILE *fd; 
    fd = fopen ("data.log", "w");
    fprintf(fd, "INFO: Calling function realloc...\n");

    if(ptr == NULL) {
        return my_malloc(size);
    }
    if(size == 0) {
        my_free(ptr);
        return NULL;
    }

    int *pointer = ptr - sizeof(size_t); 
    int old_size = *pointer - sizeof(size_t);
    *pointer = size + sizeof(size_t);
    if(size > old_size){
        fprintf(fd, "WARN: size provided bigger than old size, can't reallocate\n");
    }

    fprintf(fd, "INFO: Successfully reallocate %ld bytes at %p \n",size,ptr);
    return ptr;
}
