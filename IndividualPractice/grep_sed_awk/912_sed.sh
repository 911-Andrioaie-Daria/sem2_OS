#!/bin/sh
# delete all the characters after the last space from each line from a file

sed -E "s/ [^ ]*$/ /" input.txt
