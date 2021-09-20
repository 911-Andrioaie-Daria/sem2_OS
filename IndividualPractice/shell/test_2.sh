#!/bin/sh
# Write a shell script that receives as command line arguments a character sequence without whitespaces followed by any number of folder names. The script will count the number of regular files from each folder (recursive) that contain the given sequence in thei name but not in their content. Report the number of files that meet the criteria for each folder. The script will perform all necessary checks.


if [ $# -lt 2 ]; then
	echo Not enough arguments.
	exit 1
fi

sequence=$1
#echo $sequence
shift 1 

while [ $# -ne 0 ]; do
	dir=$1
	if [ -d $dir ]; then 
		n=0
		for file in `find $dir -type f -name "*$sequence*"`; do
			if ! grep -E -q "$sequence" $file; then
				n=`expr $n + 1`
			fi
		done
		echo $file $n
	fi
	shift 1
done 
