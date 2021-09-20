#!/bin/sh
# The script receives as command line argument a directory. Check that it is a directory and searchrecursively:
#   -display the name of files with the .sh extension
#   -if not, display the number of lines in the file.

if [ $# -lt 1 ]; then
	echo Provide an argument.
	exit 1
fi

if [ -d $1 ]; then
	for file in `find $D`; do
		if file $file | grep -E -q "POSIX shell script"; then
			echo $file has the .sh extension.
		else
			n=`wc -l $file | awk '{print $1}'`
			echo $file has $n lines.
		fi

	done
else
	echo The argument is not a directory.
fi
