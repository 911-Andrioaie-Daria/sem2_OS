#!/bin/sh
#4. Write a bash script that sorts all files given as command line arguments descending by size.(first check if an argument is a file).

touch sorted.txt

for file; do
	if [ -f $file ]; then
		s=`ls -l $file | awk '{print $5}'`
		l=$s" "$file
#		echo $file
		echo $l >> sorted.txt
	fi
done

#cat sorted.txt

sort sorted.txt | uniq | awk '{print $2}'

rm sorted.txt
