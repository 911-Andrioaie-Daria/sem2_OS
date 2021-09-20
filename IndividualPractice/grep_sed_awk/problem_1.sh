#! /bin/sh
# Find all the users that logged in from "economica" on a Sunday.

last | awk ' index($3, "economica")>0 && index($4, "Sun")>0 && length($4)==3 {print $1}' | sort|uniq
