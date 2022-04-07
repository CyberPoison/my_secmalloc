#include <stdio.h>
#include <criterion/criterion.h>
#include <../src/my_secmalloc.c>

void setup(void) {
    puts("Runs before the test");
}

test(){
    size_t size = 1078;
    int *pointer = my_malloc(size);
    my_free(pointer);
}

void teardown(void) {
    puts("Runs after the test");
}
