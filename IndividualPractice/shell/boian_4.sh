#!/bin/sh
#Find recursively in a given directory all the symbolic links, and report those that poin#t to files/directories that no longer exist. Use operator -L to test if a path is a symb#olic link, and operator -e to test if it exists (will return false if the target to whic#h the link points does not exist).

D=$1
find $D | while read F; do
	#echo $F
	if test -L $F; then
		if ! test -e $F; then
			echo $F
		fi
	fi 

done
