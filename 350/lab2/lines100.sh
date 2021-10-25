#!/bin/bash
# create a file of 100 lines

if [ -e numbs ]; then
	echo "appending to file that already exists" 
else 
	echo "creating and appeneding file"
	touch numbs
fi

for n in $(seq 1 100);
do 
	echo "$n" >> numbs
done
