INPUT_TMP="tmp.txt"

echo asd > $INPUT_TMP

SHA1=($(sha1sum ${INPUT_TMP}))
MYSHA1=($(echo "SHA1 ${INPUT_TMP}" | ./rhasher))

if [[ $SHA1 != $MYSHA1 ]];
then
	echo "SHA1 test: FAILED"
else
	echo "SHA1 test: OK"
fi

rm -f $INPUT_TMP