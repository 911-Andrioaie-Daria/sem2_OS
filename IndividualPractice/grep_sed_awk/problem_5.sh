#!/bin/sh
# Find the full names of all the users whose username ends in 88.

#awk -F: '{
#	if($1 % 100 == 88)
#		print $5
#}' /etc/passwd

grep "^[^:]*88:" /etc/passwd | awk -F: '{print $5}' | wc -l
