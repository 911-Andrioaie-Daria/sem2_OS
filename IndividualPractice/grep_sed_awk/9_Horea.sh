#!/bin/sh
# Display the number of lines in a file.

awk '{print NR}' /etc/passwd | tail -1

