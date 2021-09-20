#!/bin/sh
# A folder name is received as command line argument
# The script will search recursively in the folder and will display
#    - the names of the files that do NOT have the .txt extension
#    - the names of the files that Do have the .txt  extension but replacing all lowercase vowels with uppercase vowels
#     Perform all necessary checks.

if [ $# -lt 1 ]; then
	echo You need to provide at least one argument.
	exit 1
elif [ $# -gt 1 ]; then
	echo Only the first argument is taken into consideration.

fi

D=$1

for file in `find $D`; do
	if ! echo $file | grep -E -q "\.txt$"; then
		echo BRANCH 1:       $file does NOT have the .txt extension.
	fi
	if echo $file | grep -E -q "\.txt$"; then
		ls $file | sed -E "y/aeiou/AEIOU/"
	fi

done
