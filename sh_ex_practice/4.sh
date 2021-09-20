#!/bin/bash

dir=$1

for file in `find "$dir" -type f`; do
	if [ -L "$file" ] && [ ! -e "$file" ]; then
		echo "$file"
	fi
done
