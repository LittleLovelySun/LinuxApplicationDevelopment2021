TRASH = *.so *.o *.exe *.out *.in move *.log


move: move.c
	gcc $^ -o $@

fake_remove: fake_remove.c
	gcc -shared -fPIC  $^ -o fake_remove.so -ldl

test: test_fake test_errors

test_fake: move fake_remove
	@echo 123 > PROTECT_input.in
	@LD_PRELOAD=`pwd`/fake_remove.so ./move PROTECT_input.in output.out
	@if [ -f PROTECT_input.in ]; then echo "Test for LD_PRELOAD: OK"; else echo "Test for LD_PRELOAD: FAILED"; fi

test_errors: test_error.sh move
	@echo 1 > gold.in
	@bash ./test_error.sh

clean:
	rm -f $(TRASH)