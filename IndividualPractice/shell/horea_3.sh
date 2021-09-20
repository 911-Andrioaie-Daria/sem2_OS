#!/bin/sh
# 3. Write a script that receives as command line arguments pairs consisting of a filename and a word. For each pair, check if the given word appears at least 3 times in the file and print a corresponding message.

if [ $# -lt 2 ]; then
	echo "Not enough arguments."
	exit 1
fi

if [ $(($# % 2)) -eq 1 ]; then
	echo "You must provide an even number of arguments"
	exit 1
fi

while [ $# -gt 1 ]; do
	name=$1
	word=$2

	if [ ! -f $name ]; then
		echo The name does not belong to a file
	else
		echo $name
		count=`grep -E -c "\<$word\>" $name`
		echo $count
		if [ $count -ge 3 ]; then
			echo "Word $word appears $count times in $name"
		fi
	fi
	shift 2
done
