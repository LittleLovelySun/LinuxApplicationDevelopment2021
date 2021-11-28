#include "tests.h"

int
main(int argc, char **argv)
{
    /* volatile due to setjmp() / longjmp() */
    volatile int count_pass = 0;
    volatile int count_fail = 0;

    long *ai = 0;

    /* buf_grow(), buf_trunc() */
    buf_grow(ai, 1000);
    TEST("grow 1000", buf_capacity(ai) == 1000);
    TEST("size 0 (grow)", buf_size(ai) == 0);
    buf_trunc(ai, 100);
    TEST("trunc 100", buf_capacity(ai) == 100);
    buf_free(ai);

    return count_fail != 0;
}
