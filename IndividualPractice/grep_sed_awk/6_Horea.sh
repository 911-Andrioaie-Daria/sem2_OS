#!/bin/sh
# Display all the files from the current folder that have read permissions for the owner, group and other.

ls -l | grep -E "^-r..r..r.."
