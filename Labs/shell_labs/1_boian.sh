#!/bin/sh

ps aux | awk '{print $1}' | sort | uniq -c
