#! /bin/bash

file='compilation.ord'
out=''

while read -r line
do
	out+="$line "
done < $file

gcc -Wall -Wextra $out
