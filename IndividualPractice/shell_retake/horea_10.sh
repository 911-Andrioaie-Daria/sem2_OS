#!/bin/sh
# 10. Write a script that receives program/process names as command line arguments. The script will monitor all the processes in the system, and whenever a program with one of those names is run, the script will kill it and display a message. (see commands ps, kill, killall).

while true; do
	for bad; do
		if `ps -ef | grep -E -q "\<$bad\>"`; then
			killall $bad
			echo "Killed $bad"		
		fi
	done
	sleep 1
done
