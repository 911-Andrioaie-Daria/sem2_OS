#!/bin/sh
# 12. Write a script that finds recursively in the current folder and displays all the regular files that have write permisions for everybody (owner, group, other). Then the script removes the write permissions from everybody. Hint: use chmod's symbolic permissions mode (see the manual).

find . -type f -perm /a=r | while read file; do
	echo $file
	chmod a+w $file
done
