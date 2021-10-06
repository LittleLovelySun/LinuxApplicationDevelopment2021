GENERATES = prog prog-a prog-so *.so *.a README
TRASH = *.o *~ o.* *.log
CFLAGS = -Wall -fPIC

all: README prog prog-a prog-so

liboutput_static.a: fun.o const.o
	ar -rcs $@ fun.o const.o

liboutput.so: fun.o const.o
	cc -shared fun.o const.o -o $@


prog: const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	cc -L. prog.o liboutput_static.a -o $@

prog-so: prog.o liboutput.so
	cc -L. prog.o liboutput.so -o $@

test: test1 test2 test3


test1: prog prog-a prog-so
	./prog > $@.log 2> /dev/null
	./prog-a > $@_a.log 2> /dev/null
	LD_LIBRARY_PATH=`pwd` ./prog-so	> $@_so.log 2> /dev/null
	cmp $@.log $@_a.log
	cmp $@.log $@_so.log

test2: prog prog-a prog-so
	./prog 1 > $@.log 2> /dev/null
	./prog-a 1 > $@_a.log 2> /dev/null
	LD_LIBRARY_PATH=`pwd` ./prog-so	1 > $@_so.log 2> /dev/null
	cmp $@.log $@_a.log
	cmp $@.log $@_so.log

test3: prog prog-a prog-so
	./prog 1 2 3 > $@.log 2> /dev/null
	./prog-a 1 2 3 > $@_a.log 2> /dev/null
	LD_LIBRARY_PATH=`pwd` ./prog-so	1 2 3 > $@_so.log 2> /dev/null
	cmp $@.log $@_a.log
	cmp $@.log $@_so.log


README: prog
	./$< 2> $@

fun.o: outlib.h

clean:
	rm -f $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)