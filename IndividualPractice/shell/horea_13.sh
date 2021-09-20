#!/bin/sh
# 13. Consider a file containing a username on each line. Generate a comma-separated string with email addresses of the users that exist. The email address will be obtained by appending "@scs.ubbcluj.ro" at the end of each username. Make sure the generated string does NOT end in a comma.

users=$1
email="@scs.ubbcluj.ro"
s=""

for user in `cat $users`; do
	s+=$user$email,
done

s=`echo $s | sed -E "s/,$//"`
echo $s
