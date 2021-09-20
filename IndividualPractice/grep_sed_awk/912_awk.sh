#!/bin/sh
# Display the artihmetic average of the numbers on even positions from the odd numbered lines. Display the line number and the average.

awk 'NR % 2 == 1 {
	          n = 0;
		  s = 0;
                  for(f=2; f<= NF; f=f+2){
		      s = s+ $f;
                      n = n+1;
		  }
		if(n!=0)
		  print NR " "  s/n
		}' numbers.txt
