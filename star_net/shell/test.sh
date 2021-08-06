#!/bin/bash


function getsyscpu
{
	cpuidle=$(vmstat 1 5 | sed -n '3,$p'\
	| awk '{x = x + $15} END {print x/5}'\
	| awk -F. '{print $1}')
	cpunum=`echo "100-$cpuidle"|bc`
	echo $cpunum
}



NUM=3
CPU=$1
DATE=`date`
LOGNAME=ROKUDOU
while [ $NUM -gt 0 ];do
	if [ $CPU -gt 90 ];then
		RESULT=2
	elif [ $CPU -lt 10 ];then
		RESULT=0
	else
		RESULT=1
	fi
	
	case RESULT in 
		"2")printf "hello %s ,the usage of sys cpu is %s,too high!\n\
				System Date is :%s\n" "LOGNAME" "$CPU" "$DATE";;
		"0")echo "hello $LOGNAME ,the usage of sys cpu is $CPU,too low!\n\
				System Date is :$DATE";;
		"1")echo "hello $LOGNAME ,the usage of sys cpu is $CPU,normal!\n\
				System Date is :$DATE";;
		*);;
	esac
	
#	NUM=`expr $NUM -1` 
	sleep 5
done


