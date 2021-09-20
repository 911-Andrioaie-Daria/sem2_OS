#!/bin/bash
#Display all the distinct lines eft in /etc/passwd after deleting all characters except "r".

sed -E "s/[^r]//g" /etc/passwd | sort | uniq
