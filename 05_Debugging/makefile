TRASH = range *.gdbout *.output

range: range.c
	cc $^ -O0 -g -o $@

clean:
	rm -f $(TRASH)

test: test1

test1: test1.gdb
	gdb --batch  --command=$^ ./range | grep "@@@.*" | sed 's/@@@//gi' > test1.gdbout
	cmp --silent test1.gold test1.gdbout && echo "Test1: ok" || echo "Test1: failed"
