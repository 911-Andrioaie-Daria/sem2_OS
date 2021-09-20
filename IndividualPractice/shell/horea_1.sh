#!/bin/sh
# 1. Write a bash script that calculates the sum of the sizes (in bytes) of all regular files in a folder given as a parameter.(use test to check if the folder exists and if a given file is a regular file)

D=$1
sum=0

for file in `find $D -type f`; do
	n=`ls -l $file | awk '{print $5}'`
#	m=`wc -c $file | awk '{print $1}'`
#	echo $m
	sum=`expr $sum + $n`
done

echo "The sum of the sizes is $sum"
