IFS=''
text=""

x=()
y=()

len=0
total_len=0

time=${1:-0.01}

while read -r line
do
	col=0
	for (( i=0; i < ${#line}; i++ ))
	do
		if [ ${line:$i:1} != " " ]
		then
			text="$text${line:$i:1}"
			x+=($col)
			y+=($len)
			total_len=$(($total_len + 1))
		fi

		col=$(($col + 1))
	done

	len=$(($len + 1))
done

IFS=$' \t\n'
idx=($(seq 0 $(($total_len - 1)) | shuf))

tput clear

for id in ${idx[@]}
do
	tput cup  ${y[id]} ${x[id]}
	echo ${text:$(($id)):1}
	sleep $time
done


tput cup $(($len + 5)) 0