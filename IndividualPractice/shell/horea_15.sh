#!/bin/sh
# 15. Write a shell script that, for all the users in /etc/passwd, creates a file with the same name as the username and writes in it all the ip addresses from which that user has logged in. (hint: use the last command to find the ip addresses).

extension=".txt"
for username in `cat /etc/passwd | sed -E "s/:.*//"`; do
	#echo $username
	filename=$username$extension
	touch "$filename"
	last | grep -E "$username" | awk '{print $3}' >> $filename
	nr=`wc -l $filename | sed -E "s/ .*//"`
	if [ $nr -ne 0 ]; then
		cat $filename
	fi
	rm $filename
done
