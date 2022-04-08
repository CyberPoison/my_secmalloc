#include <stdio.h>
#include "../include/my_secmalloc.h"
#include <sys/mman.h>

int main(){
    size_t size = 1078;

    int *pointer = my_malloc(size);
    int *pointer2 =  my_calloc(20, 40);
    int *pointer3 = my_realloc(pointer,45);
    my_free(pointer);
    
    return 0;
}
