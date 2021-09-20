#!/bin/bash
# Calculate the average of the PID's of the processes currently running in the system.

ps -ef | awk 'BEGIN{s=0; n=0}{s=s+$2; n++;} END{print s/n}' 
