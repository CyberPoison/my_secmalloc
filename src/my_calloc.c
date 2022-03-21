#include <stdio.h>
#include "../include/my_secmalloc.h"
#include <sys/mman.h>
#include <string.h> // to remove after tests.

// printf = log to put in file later

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
