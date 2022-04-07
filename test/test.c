#include <stdio.h>
#include <criterion/criterion.h>
#include <../src/my_secmalloc.c>
#include <signal.h>

void setup(void) {
    puts("Runs before the test");
}

Test(sample, passing, .signal = SIGSEGV){
    int *pointer = my_malloc(1080);
    my_free(pointer);
}

void teardown(void) {
    puts("Runs after the test");
}
