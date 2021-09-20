#!/bin/sh

if test $# -eg 0; then
	echo No params
	exit 0
fi

while true; do
	for X; do
		echo "X: $X"
		ps -ef | awk -v fisier=$X '{if(index($NF, fisier)>0) print $0}'		done
done
