#!/bin/sh
# display the username and pid of all the processes that are run by an examn account with odd digits after the ex and have a pid of 3 digits.

ps -ef | grep -E "^ex([13579])+ +([0-9]){3}" | awk '{print $1 " " $2}'
