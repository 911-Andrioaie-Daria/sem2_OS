#!/bin/sh
# 7. Find recursively in a given directory all the symbolic links, and report those that point to files/directories that no longer exist. Use option -L to test if a path is a symbolic link, and option -e to test if it exists (will return false if the target to which the link points does not exist)

D=$1
for file in `find $D -type l`; do
	if [ ! -e $file ]; then
		echo $file points to inexistent file.
	fi

done
