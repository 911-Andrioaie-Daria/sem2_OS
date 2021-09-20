#!/bin/sh
#Write a script that receives dangerous program names as command line arguments. The script will monitor all the processes in the system, and whenever a program known to be dange#rous is run, the script will kill it and display a message.

if test $# -eq 0; then
	echo No parameters
	exit 0
fi

while true; do
	for X; do
		ps -ef | awk -v name=$X '{if(index($8, name)>0 && length($8)==length(name)) print $2}' | while read pid; do
			kill $pid
			echo Killed $pid

		done 
	done
	sleep 1
done
