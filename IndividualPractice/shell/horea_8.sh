#!/bin/sh
# 8. Write a bash script that receives a folder name as argument. Find recursively in the folder the number of times each file name is repeated.

if [ ! -d $1 ]; then
	echo $1 is not a directory
	exit 1
fi

#for file1 in `find $1 -type f`; do
#	name1=`awk -F/ '{print $NF}' $file1`
#	echo $file1
#	echo $name1
#	repeat=0
#	for file2 in `find $1 -type f`; do
#		if [ "$file1" != "$file2" ]; then
#   			name2=`awk -F/ '{print $NF}'`
#			if [ "$name1" == "$name2" ]; then
#				repeat=`expr $repeat + 1`
#			fi
#		fi
#	done
#	echo File $file1 is repeated $repeat times.
#
#done

find $1 -type f | awk -F/ '{print $NF}' | sort | uniq -c | sort -n
