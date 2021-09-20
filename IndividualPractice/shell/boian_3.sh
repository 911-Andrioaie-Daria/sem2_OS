#!/bin/sh
# Find recursively in a directory, all the files with the extension ".log" and sort their lines (replace the original file with the sorted content).

D=$1

find $D -name "*.txt" | while read F; do
	touch aux_file.txt
	sort $F > aux_file.txt
	mv aux_file.txt $F
done

