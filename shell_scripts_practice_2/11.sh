#!/bin/bash

dir=$1

for file in `find $dir -type f`; do
	file_name=`echo "$file" | grep -E -o "/[a-zA-Z0-9]+\." | grep -E -o "[^/\.]+"`
	if [[ `echo "$file_name" | grep -E "[a-zA-Z0-9]{5}"` ]]; then
		echo "$file_name"
	fi
	echo "$file_name"
done
