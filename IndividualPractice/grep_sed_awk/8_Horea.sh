#!/bin/sh
# For each file in the current directory, display only the owner's permissions and the filename.

ls -l | sed -E "s/^(.)//" | sed -E "s/(...)(.{6})/\1/" |awk '{print $1, $9}'
