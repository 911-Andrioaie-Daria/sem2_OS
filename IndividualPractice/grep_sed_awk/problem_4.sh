#!/bin/bash
# Display all the distinct TTY's used by the user root.

ps -ef | awk 'index($1, "root")>0 {print $6}' | sort | uniq
