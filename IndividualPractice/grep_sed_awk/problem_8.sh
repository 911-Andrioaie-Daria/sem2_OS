#!/bin/sh
#Find all the distinct usernames starting with "r" that are currently running programs and display them duplicating every vowel
ps -ef | grep -E "^r" | awk '{print $1}' | sort | uniq | sed -E "s/([aeiou])/\1\1/gi"
