#!/bin/sh
# Replace dialogue lines with quoted lines.
# Remove all empty lines
# For the lines that contain Hagrid, print only the two words and the initial number of words on that line.

#sed -E "/^$/d" hagrid.txt | grep -E "^-" | sed -E "s/-/\"/" | sed -E "s/$/\"/"
#grep -E "\<Hagrid\>" hagrid.txt | awk '{print $1, $2, NF}'

#sed -E "s/-/\"/" | sed -E "s/$/\"/" hagrid.txt

grep -E -v "^$" hagrid.txt | sed -E "s/-/\"/" | sed -E "s/(^\".*)($)/\1\"/" | awk '{found_hagrid = 0
                                                                                    for(i=1; i<=NF; i++) if($i ~ /\<Hagrid\>/) found_hagrid = 1
                                                                                    if(found_hagrid == 1)
                                                                                         print $1, $2, NF
                                                                                    else
                                                                                         print $0}' 
