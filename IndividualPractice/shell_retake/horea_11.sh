#!/bin/sh
# 11. Write a script that receives a directory as a command line argument. The script will delete all the C source files from the directory and will display all other text files sorted alphabetically.

if [ $# -lt 1 ]; then
	echo "Please provide an argument"
	exit 1
fi

dir=$1
if [ -e text_files.txt ]; then
	rm text_files.txt
fi

touch text_files.txt
	

if [ -d $dir ]; then
	for file in `find $dir -type f`; do
		if file $file | grep -E -q "\<C\>"; then
			echo "Removed $file"
			rm $file
		elif file $file | grep -E -q "ASCII text" && ! echo $file | grep -E -q "text_files.txt$"; then
			echo $file >> text_files.txt
		fi
	done
else
	echo "Argument is not a directory"
	exit 1
fi

sort text_files.txt | uniq
rm text_files.txt
