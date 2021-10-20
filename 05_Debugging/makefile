TRASH = range *.gdbout *.output *.txt

range: range.c
	cc $^ -O0 -g -o $@

test: range test1 test2

test1: test1.gdb
	gdb --batch  --command=$^ ./range | grep "@@@.*" | sed 's/@@@//gi' > test1.gdbout
	cmp --silent test1.gold test1.gdbout && echo "Test1: ok" || echo "Test1: failed"

test2: test2.gdb
	gdb --batch  --command=$^ ./range | grep "@@@.*" | sed 's/@@@//gi' > test2.gdbout
	cmp --silent test2.gold test2.gdbout && echo "Test2: ok" || echo "Test2: failed"

clean:
	rm -f $(TRASH)
