#!/bin/bash
# Find all usernames starting with "t" that logged on "pts/9".

last | awk '{if(index($2,"pts/9")>0) if(length($2)==5) print $1}' | grep "^t" | sort | uniq
