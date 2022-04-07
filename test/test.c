#include <stdio.h>
#include <criterion/criterion.h>
#include "../src/my_secmalloc.c"

void setup(void) {
    puts("Runs before the test");
}
#if 0
Test(sample, test){
    int *pointer = my_malloc(1080);
    cr_expect(sizeof(pointer) == 1080, "OK");
    my_free(pointer);
}
#endif

Test(sample, test) {
    cr_expect(strlen("Test") == 4, "Expected \"Test\" to have a length of 4.");
    cr_expect(strlen("Hello") == 4, "This will always fail, why did I add this?");
    cr_assert(strlen("") == 0);
}

void teardown(void) {
    puts("Runs after the test");
}

