#include <stdlib.h>
#include "../include/my_secmalloc.h"

void *calloc(size_t nmemb, size_t size) {
    return my_calloc(nmemb, size);
}

void *malloc(size_t size) {
    return my_malloc(size);
}

void free(void *ptr) {
    return my_free(ptr);
}

void *realloc(void *ptr, size_t size) {
    return my_realloc(ptr, size);
}
