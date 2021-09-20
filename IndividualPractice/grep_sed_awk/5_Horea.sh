#!/bin/sh
# Dispplay the number of lines in a file that contain only non-alphanumerical characters.

grep -E "^[^a-zA-Z0-9]*$" file.txt | wc -l

