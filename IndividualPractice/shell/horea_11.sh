#!/bin/sh
# 11. Write a script that receives a directory as a command line argument. The script will delete all the C source files from the directory and will display all other text files sorted alphabetically.

if [ $# -ne 1 ]; then
	echo Provide one directory.
	exit 1
fi

if [ ! -d $1 ]; then
	echo The argument has to be a directory.
	exit 1
fi

touch text_files.txt

for file in `find $D -type f`; do
	if file $file | grep -E -q "ASCII text"; then
		echo $file >> text_files.txt
	fi

	if file $file | grep -E -q "C program"; then
		echo $file
	fi
done

sort text_files.txt | uniq
rm text_files.txt
