#!/bin/sh
# Display all the mounted file systems who are either smaller than than 1GB or have less than 20% free space.

#TODO add the % back after the free space stat.
df -m | awk '{if($2 < 100000) print $0}' | sed -E "s/%//" | awk '{if($5>80) print $0}' | sed -E "s/(^([^ ]+ ){5})( )/\1% /"
