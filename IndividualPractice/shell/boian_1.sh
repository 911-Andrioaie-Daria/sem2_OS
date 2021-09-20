#!/bin/sh
# Display a report showing the full name of all the users currently connected and the number of processes belonging to each of them. (who, ps, finger, grep, while, wc)

who | sed -E "s/(^[a-zA-Z0-9]+)( .*)/\1/ " | while read user; do
	number_of_processes=`ps -u $user | wc -l`
	echo $user $number_of_processes
done
