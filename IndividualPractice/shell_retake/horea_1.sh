#!/bin/sh
# 1. Write a bash script that calculates the sum of the sizes (in bytes) of all regular files in a folder given as a parameter.(use test to check if the folder exists and if a given file is a regular file) 

if [ $# -lt 1 ]; then
	echo "Provide one argument"
	exit 1
fi

dir=$1

if [ -d $dir ]; then
	s=0
	for file in `find $dir -type f`; do
		n=`ls -l $file | awk '{print $5}'`
		s=`expr $s + $n`  
		echo $file has size $n
	done
	echo The sum of sizes is $s
else
	echo "The argument is not a directory"
	exit 1
fi
