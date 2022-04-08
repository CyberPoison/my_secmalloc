#include <stdio.h>
//#include <criterion/criterion.h>
#include "../src/my_secmalloc.c"
#include <assert.h>

#if 0
void setup(void) {
    puts("Runs before the test");
}

Test(sample, test) {
    cr_expect(strlen("Test") == 4, "Expected \"Test\" to have a length of 4.");
    cr_expect(strlen("Hello") == 4, "This will always fail, why did I add this?");
    cr_assert(strlen("") == 0);
}

void teardown(void) {
    puts("Runs after the test");
}
#endif

void test_malloc() {
    size_t size = 1078;
    int *pointer = my_malloc(size);
    assert(sizeof(pointer) == 1078);
}

int main() {
    test_malloc();

    return 0;
}
