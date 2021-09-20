#!/bin/sh
# display all users in the system whose username starts with a vowel.

grep -E "^[aeiouAEIOU]" /etc/passwd
