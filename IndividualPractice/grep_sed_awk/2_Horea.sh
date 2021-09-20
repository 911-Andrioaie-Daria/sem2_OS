#!/bin/sh
# Display the names of the student whose user id contains only even digits.

grep -E "^[a-z]{4}[02468]{4}" /etc/passwd | awk -F: '{print $5}'
