#!/bin/sh
#Display the full names of the users having a username that starts with 'm' and the user id divisible by 7.

grep -E "^m" /etc/passwd | awk -F: '$3 % 7 == 0 {print $5}'
