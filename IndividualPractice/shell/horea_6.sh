#!/bin/sh
# 6. Write a(alalal) script that monitors the state of a given folder and prints a message when something changed.
D=$1

prev_state=""
while true; do
	current_state=""
	for file in `find $D`; do
		if [ -f $file ]; then		
			LS=`ls -l $file | sha1sum`
			CONTENT=`sha1sum $file`
		fi
		
		if [ -d $file ]; then
			LS=`ls -l -d $file | sha1sum`
			CONTENT=`ls -l $file | sha1sum`
		fi
		current_state="$current_state\n$LS $CONTENT"	
	
	done
	if test -n "$prev_state" && test "$current_state" != "$prev_state"; then
		echo Something changed
	fi

	prev_state=$current_state 
	sleep 1
done
