#!/bin/sh
#	Find recursively in a directory, all the files that have write permissio#ns for everyone. Display their names, and the permissions before and after remo#ving the write permission for everybody. You will need to use chmod's symbolic #permissions mode, instead of the octal mode we have used in class. The the chmo#d manual for details.

D=$1

find $D -type f -perm w| while read file; do
	echo before:
	ls -l $file | awk '{print $1 $9]'
	chmod a-w $file
	echo after:
	ls -l $file | awk '{print $1 $9}'
done
