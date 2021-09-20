#!/bin/sh
# Find all the users that logged into the system after 11 pm.

last | awk 'index($7, "23:")>0 {print $1}' |sort|uniq
