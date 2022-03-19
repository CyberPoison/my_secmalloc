#include <stdio.h>
#include "../include/my_secmalloc.h"
#include <sys/mman.h>
#include <string.h>

// printf = log to put in file later

void *my_malloc(size_t size){
    printf("INFO: Calling malloc function...\n");
    if(size == 0){
        printf("WARN: allocating 0 bytes returning NULL pointer\n"); 
        return NULL;
    }
    int *pointeur = mmap(NULL,sizeof(size_t)+size,PROT_READ | PROT_WRITE | PROT_EXEC,MAP_PRIVATE | MAP_ANONYMOUS,-1,0);
    if(pointeur == MAP_FAILED){
        printf("ERROR: Mapping Failed\n");  
    }
    else{
       
        int *ptr = pointeur;
        pointeur += sizeof(size_t)/sizeof(int); // 8/4 = 2
        *ptr = size + sizeof(size_t);
        printf("INFO: Successfully Allocate %d bytes at %p\n",size,pointeur);
    }
    
    return pointeur;
}


void my_free(void *ptr){
    printf("INFO: Calling free function...\n");
    if(ptr != NULL){
        int *pointeur = ptr - sizeof(size_t); 
        int size = *pointeur;
        int result = munmap(pointeur,size);
        if(0 == result){
            printf("INFO: Successfully free %d bytes at %p",size - sizeof(size_t),ptr);
        }
    }else{
       printf("WARN: Performing free on NULL pointer"); 
    }
    
}

void *my_calloc(size_t nmemb, size_t size){

    printf("INFO: Calling function calloc...");
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

    int *pointeur = ptr - sizeof(size_t); 
    int old_size = *pointeur - sizeof(size_t);
    *pointeur = size + sizeof(size_t);
    if(size > old_size){
        printf("WARN: size provided bigger than old size, can't reallocate\n");
    }
    printf("INFO: Successfully reallocate %d bytes at %p \n",size,ptr);
    return ptr;
}


int main(){
    size_t size = 1078;
    int *pointeur = my_malloc(size);
    //int *pointeur2 =  my_calloc(20, 40);
    int *pointeur3 = my_realloc(pointeur,45);
    my_free(pointeur);
    
    return 0;
}