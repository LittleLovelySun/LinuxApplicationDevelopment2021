GOLD_INPUT=gold.in
INPUT=file.in
OUTPUT=file.out


{
	rm -f $INPUT $OUTPUT
	strace ./move $OUTPUT
	CODE_ERROR=$?
} &> /dev/null

if [[ $CODE_ERROR != 1 ]];
then
	echo "Test error incorrect count of arguments: FAILED"
else
	echo "Test error incorrect count of arguments: OK"
fi


{
	strace -eopenat -e fault=openat:when=3 ./move $INPUT $OUTPUT
	CODE_ERROR=$?
} &> /dev/null

if [[ -f $OUTPUT ]] || [[ $CODE_ERROR != 2 ]];
then
	echo "Test error in opening input file: FAILED"
else
	echo "Test error in opening input file: OK"
fi


{
	cat $GOLD_INPUT > $INPUT
	strace -eopenat -e fault=openat:when=4 ./move $INPUT $OUTPUT
	CODE_ERROR=$?
} &> /dev/null

if [[ -f $OUTPUT ]] || [[ $CODE_ERROR != 3 ]];
then
	echo "Test error in opening output file: FAILED"
else
	echo "Test error in opening output file: OK"
fi

{
	cat $GOLD_INPUT > $INPUT
	strace -eread -e fault=read:when=3 ./move $INPUT $OUTPUT
	CODE_ERROR=$?
}  &> /dev/null

if [[ -f $OUTPUT ]] || [[ $CODE_ERROR != 4 ]];
then
	echo "Test error reading input file: FAILED"
else
	echo "Test error reading input file: OK"
fi


{
	rm -f $INPUT $OUTPUT
	cat $GOLD_INPUT > $INPUT
	strace -eclose -e fault=close:when=3 ./move $INPUT $OUTPUT
	CODE_ERROR=$?
} &> /dev/null

if [[ -f $OUTPUT ]] || [[ $CODE_ERROR != 6 ]];
then
	echo "Test error while closing input file: FAILED"
else
	echo "Test error while closing input file: OK"
fi


{
	rm -f $INPUT $OUTPUT
	cat $GOLD_INPUT > $INPUT
	strace -eclose -e fault=close:when=4 ./move $INPUT $OUTPUT
	CODE_ERROR=$?
} &> /dev/null

if [[ -f $OUTPUT ]] || [[ $CODE_ERROR != 7 ]];
then
	echo "Test error while closing output file: FAILED"
else
	echo "Test error while closing output file: OK"
fi

{
	rm -f $INPUT $OUTPUT
	cat $GOLD_INPUT > $INPUT
	strace -eunlink -e fault=unlink:when=1 ./move $INPUT $OUTPUT
	CODE_ERROR=$?
} &> /dev/null

if [[ $CODE_ERROR != 8 ]];
then
	echo "Test error while removing input file: FAILED"
else
	echo "Test error while removing input file: OK"
fi
