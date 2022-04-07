#include <stdio.h>
#include "my_secmalloc.c"
#include "../include/my_secmalloc.h"
#include <sys/mman.h>
#include <string.h> // to remove after tests.

int main(){
    size_t size = 1078;
    int *pointer = my_malloc(size);
    int *pointeur2 =  my_calloc(20, 40);
    int *pointer3 = my_realloc(pointer,45);
    my_free(pointer);
    
    return 0;
}
