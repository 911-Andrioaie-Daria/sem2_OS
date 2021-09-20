#!/bin/sh
# Display all the distinct lines left in etc/passwd after deleting all leters and digits and spaces.

#cat /etc/passwd | tr -d [:alpha] | tr -d [:digit:] | tr -d [:space:] | sort | uniq | less

sed -E "s/[a-z]*[0-9]* *//gi" /etc/passwd |sort |uniq
