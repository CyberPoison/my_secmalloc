#include <stdio.h>
#include <criterion/criterion.h>
#include <../src/my_secmalloc.c>

void setup(void) {
    puts("Runs before the test");
}

Test(){
    
}

void teardown(void) {
    puts("Runs after the test");
}
