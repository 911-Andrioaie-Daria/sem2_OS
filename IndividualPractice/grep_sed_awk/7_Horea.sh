#!/bin/sh
# Display how many times a user has logegd in the system

last | grep -E "adie2854" | wc -l
