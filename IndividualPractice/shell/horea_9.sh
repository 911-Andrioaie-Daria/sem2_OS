#!/bin/sh
# 9. Calculate the average of all process ids in the system per user.

ps -ef | awk '{print $1}' | sort | uniq | while read user; do
	sum=0
	count=0
	for pid in `ps -u $user | awk 'NR>1{print $1}'`; do
		sum=`expr $sum + $pid`
		count=`expr $count + 1`
	done
	average=`expr $sum / $count`
	echo Average of $user is $average
		
	
done
