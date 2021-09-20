#!/bin/sh
#Display the session count and full names of all the users who logged into the system this month, sorting the output by the session count in descending order. Use the -s and/or -t options of command last to get this month's sessions, and the command date to generate the required timestamp in the expected format.

D=`date +%Y%m`
T="${D}01000000"

last -t $T | sort | uniq -c | sort -nr | while read sessions user_info
