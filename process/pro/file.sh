#!/bin/bash
declare -i n=1
declare -i m=1
declare -i t=1

while [ $n -lt 7 ]
do
	mkdir $1/$n
	m=1
	for loop in 1 2 3 4 5
	do
			echo "$1/$n/$m $loop " >> $1/$n/$m.txt
		
	done 		

				
	n=$n+1
done		
