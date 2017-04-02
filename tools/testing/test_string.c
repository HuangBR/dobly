#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "../../include/string.h"

void strnlen_test(void **state)
{
    char *s = "helloc";

    assert_int_equal(strnlen(s, 8), 6);
    assert_int_equal(strnlen(s, 5), 5);
}

void memset_test(void **state)
{
    char s[10] = "helloc";

    assert_string_equal(memset(s, '\0', 0), "helloc");
    assert_string_equal(memset(s, 'a', 2), "aalloc");
    assert_string_equal(memset(s, 'h', 1), "halloc");
    assert_string_equal(memset(s+1, 'e', 1), "elloc");
    assert_string_equal(s, "helloc");
}

void memcpy_test(void **state)
{
    const char *s = "hello world";
    char d[20];

    memset(d, '\0', 20);

    assert_string_equal(memcpy(d, s, 5), "hello");
    
    memset(d, '\0', 5);
    assert_string_equal(memcpy(d, s+2, 3), "llo");
}

int main(int argc, char *argv[])
{
    const UnitTest tests[] = {
        unit_test(strnlen_test),
        unit_test(memset_test),
        unit_test(memcpy_test),
    };

    return run_tests(tests);
}
