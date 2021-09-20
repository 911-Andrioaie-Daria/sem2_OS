#!/bin/sh
# For all arguments that are representing directories count the number of
# files that the current user is the owner of.

if test $# -lt 1; then
	echo "Usage: $0 [dirs...]" 
	exit 1
fi
for p; do
	if test -d $p; then
		find $p -type f | while read v; do
			ls -l $v | awk -v u=$USER '{ if(index($u, $3) > 0) print $0}'
		done | wc -l
	fi
done
