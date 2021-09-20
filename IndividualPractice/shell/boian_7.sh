#!/bin/sh
#Consider a file containing a username on each line. Generate a comma-separated string with email addresses of the users that exist. The email address will be obtained by appending "@scs.ubbcluj.ro" at the end of each username. Make sure the generated string does NOT end in a comma.

if test $# -eq 0; then
	echo No file provided
	exit 0
fi

email="@scs.ubbcluj.ro"
s=""
file=$1
total_lines=`cat $file | wc -l`
echo $total_lines
current_line=1

#for user in `cat $file`; do
#	s+=$user$email,
#done
#echo $s > aux_file.txt
#sed -E "s/,$//" aux_file.txt
#s=`cat aux_file.txt`
#echo $s

for user in `cat $file`; do
	if test $current_line -lt $total_lines; then
		s+=$user$email,
		current_line=`expr $current_line + 1`
	else
		s+=$user$email
	fi
done
echo $s
