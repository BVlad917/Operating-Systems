#!/bin/bash

dir=$1

for file in `find $dir -type f`; do
	if `grep -q "Successful" $file`; then
		echo "$file"
	fi
done
