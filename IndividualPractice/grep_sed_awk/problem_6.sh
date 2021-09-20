#!/bin/bash
# Find all users whose user id has 3 digits and starts with 23

grep -E "^([^:]+:){2}23" /etc/passwd | awk -F: 'length($3)==3 {print $5}'
