#!/bin/sh
#Write a script that finds in a given directory hierarchy, all duplicate files and displays their paths. Hint: use checksums to detect whether two files are identical.

find $1 -type f | while read file1; do
	find $1 -type f | while read file2; do
		if test $file1 != $file2; then
			content1=`sha1sum $file1 | awk '{print $1}'`
			content2=`sha1sum $file2 | awk '{print $1}'`
			if test "$content2" == "$content1"; then
				echo $file1
			fi

		fi
	done
done
