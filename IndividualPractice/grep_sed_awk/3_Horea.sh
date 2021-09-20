#!/bin/sh
#Display the name and group of all students from odd numbered groups

cut -d: -f5,6 /etc/passwd | grep -E "^.*:/home/scs/.*/gr[0-9]{2,}[13579]/" | awk -F/ '{print $1 " " $6}'
