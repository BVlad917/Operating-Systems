#!/bin/bash

dir=$1

for file in `find "$dir" -type f -name "*.log"`; do
	#cat "${file}" | sort > temp.log
	#cat temp.log > "$file"
	#rm temp.log
	sort $file > tmp
	mv tmp $file""
done
