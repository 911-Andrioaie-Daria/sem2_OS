#!/bin/sh
# 2. Write a script that reads filenames until the word "stop" is entered. For each filename, check if it is a text file and if it is, print the number of words on the first line.(Hint: test command to check if regular file; file command to check if text file)


while read name; do
	if test $name == "stop"; then
		break
	fi
	if [ -f $name ] && file $name | grep -E -q "ASCII text"; then
			echo $name
			nr=`awk 'NR == 1{print NF}' $name`
			echo $nr
	fi
done
