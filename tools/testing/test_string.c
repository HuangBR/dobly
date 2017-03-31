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

int main(int argc, char *argv[])
{
    const UnitTest tests[] = {
        unit_test(strnlen_test),
    };

    return run_tests(tests);
}
