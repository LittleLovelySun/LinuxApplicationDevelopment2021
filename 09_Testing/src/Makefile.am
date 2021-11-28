CFLAGS = -std=c99 -Wall -Wextra -pedantic
if COND_GCOV
CFLAGS  += -O0 -g -fprofile-arcs -ftest-coverage
endif

lib_LTLIBRARIES = libgrowbuf.la

libgrowbuf.c: buf.h

gcov:
	gcov .libs/libbuf -j