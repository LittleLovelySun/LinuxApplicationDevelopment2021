set pagination off
set logging on

break 17 if i >= 28 && i <= 35
	command 1
	printf "@@@start=%d, stop=%d, step=%d, current=%d\n", N, M, S, i
	continue
end


run -100 100 3 > /dev/null

set logging off
quit