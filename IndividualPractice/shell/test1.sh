#!/bin/sh
# Shell script that receives as command line arguments a character sequence followed by any number of characters.
# -if the argument is a regular file, report if the file contains that sequence
# - if the argument is a folder, it will report if it contains an item with the name equal to the character sequence 
#  - else, ignore the argument
# The script will perform all necessary checks.

if [ $# -lt 1 ]; then
	echo Not enough arguments.
	exit 1
fi

sequence=$1
shift

for a; do
	if [ -f $a ]; then
		if grep -E -q "$sequence" $a; then
			echo The file $a contains $sequence
		fi
	elif [ -d $a ]; then
		for file in `find $a -maxdepth 1 -name "$sequence"`; do
			echo The item $file in the folder $a has the name $sequence.

		done
	fi
done
