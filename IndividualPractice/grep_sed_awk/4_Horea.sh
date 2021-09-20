#!/bin/sh
# Display the user pid and command por each process that is not run by a student.

ps -ef | grep -E -v "^[a-z]{4}[0-9]{4}" | awk '{print $1, $2, $8}'
