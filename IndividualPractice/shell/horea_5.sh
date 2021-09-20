#!/bin/sh
#5. Write a script that extracts from all the C source files given as command line arguments the included libraries and saves them in a file.(use the file command to check if a file is a C source file)

if [ -f headers.txt ]; then
	rm headers.txt
	touch headers.txt
else
	touch headers.txt
fi

touch libraries.txt
for file; do
	if file $file | grep -E -q "C program"; then
		grep -E "#include" $file | awk '{print $2}' >> libraries.txt
	fi
done

sort libraries.txt | uniq >> headers.txt
rm libraries.txt
cat headers.txt
