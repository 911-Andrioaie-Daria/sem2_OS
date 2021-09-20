#!/bin/sh
#Write a shell script that receives as command line argument a directory. The script will search recursively in the directry and display:
#     - the name of the C source files with the .c extension
#     - the number lines in in C source files that do NOT have the .c extension

if [ $# -lt 1 ]; then
	echo Provide an argument.
	exit 1
fi

D=$1

if [ -d $D ]; then
	for file in `find $D`; do
		if file $file | grep -E -q "C program"; then
			if echo $file | grep -E -q "\.c"; then
				echo $file has the .c extension
			else
				lines=`wc -l | awk '{print $1}'`
				echo $file has $lines lines.
			fi
		
		fi
#		has_extension=`echo $file | grep -E -q "\.c"`
#		is_C_source=`file $file | grep -E -q "C source"`
#		if $has_extension && $is_C_source; then
#			echo $file
#		elif $is_C_source && ! $has_extension; then
#			lines=`wc -l | awk '{print $1}'`
#			echo $file has $lines
#		fi
	done
else
	echo The argument is not a directory.
fi 
