INPUT_TMP="tmp.txt"

echo asd > $INPUT_TMP

MD5SUM=($(md5sum ${INPUT_TMP}))
MYMD5=($(echo "MD5 ${INPUT_TMP}" | ./rhasher))

if [[ $MD5SUM != $MYMD5 ]];
then
	echo "MD5 test : FAILED"
else
	echo "MD5 test : OK"
fi

rm -f $INPUT_TMP