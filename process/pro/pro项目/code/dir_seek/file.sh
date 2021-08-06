#!/bin/bash

[ $# -ne 1 ]
if [ $? -eq 0 ]
then
	echo "usage : ./file.sh <dir_dest>"
	exit
fi


declare -i n=1
declare -i m=1
declare -i t=1

while [ $n -lt 10 ]
do
	mkdir $1/$n
	
	m=1
	while [ $m -lt 10 ]
	do
		mkdir $1/$n/$n$m

		t=1
		while [ $t -lt 10 ]
		do
			echo "$1/$n/$n$m/$n$m$t" > $1/$n/$n$m/$n$m$t.txt
			t=$t+1
		done		

		m=$m+1	
	done

	n=$n+1
done

