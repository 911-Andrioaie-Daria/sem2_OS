#!/bin/sh
# Find recursively in a directory all ".c" files having more than 500 lines. Stop after finding 2 such files.
# duplicate.txt
D=$1
S=30
found=0
find $D -name "*.c" -type f | while read F; do
 	#echo "F: *$F*"  
        nr_of_lines=`wc -l $F | awk '{print $1}'`
        #echo *$nr_of_lines*
	if [ $nr_of_lines -gt $S ]; then
		if [ $found -lt 2 ]; then
			echo $nr_of_lines  $F
			found=`expr $found + 1`
		else
			exit 0
		fi
	fi
done
