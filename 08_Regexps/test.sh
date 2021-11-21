OUTPUT_TMP="tmp.txt"
MY_OUTPUT_TMP="my_tmp.txt"
TEST_NUM=1

compare () { 
    if cmp -s "$OUTPUT_TMP" "$MY_OUTPUT_TMP"; then
        echo Test $TEST_NUM: OK
    else
        echo Test $TEST_NUM: FAILED
    fi

    TEST_NUM=$((TEST_NUM + 1))
}

# CORRECT
echo 'st st ring' | sed -E 's/(s)t/\1la/' > $OUTPUT_TMP
./esub "(s)t" "\1la" "st st ring" > $MY_OUTPUT_TMP
compare


echo 'st st ring' | sed -E 's/(s)t/bla/' > $OUTPUT_TMP
./esub "(s)t" "bla" "st st ring" > $MY_OUTPUT_TMP
compare

echo '123asd321___123asd321' | sed -E 's/([0-9]+)([a-z]+)([0-9]+)/\3\2\1/' > $OUTPUT_TMP
./esub "([0-9]+)([a-z]+)([0-9]+)" "\3\2\1" "123asd321___123asd321" > $MY_OUTPUT_TMP
compare


echo '123asd321___123asd321' | sed -E 's/([0-9]+)([a-z]+)([0-9]+)/\\\\\3\2\1/' > $OUTPUT_TMP
./esub "([0-9]+)([a-z]+)([0-9]+)" "\\\\\\\\\3\2\1" "123asd321___123asd321" > $MY_OUTPUT_TMP
compare


# ERROR
./esub "(t)(e)(s)" "\4" "test" > $MY_OUTPUT_TMP
echo "No group '4' in regexp" > $OUTPUT_TMP
compare

./esub "([a-z)" "bla" "sss" > $MY_OUTPUT_TMP
echo "regecomp() failed with  'Unmatched [ or [^'" > $OUTPUT_TMP
compare

rm -f $INPUT_TMP
rm -f $MY_OUTPUT_TMP