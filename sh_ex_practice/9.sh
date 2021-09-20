#!/bin/bash

dir=$1
files_info=""

for file in `find $dir -type f`; do
	s=`cat $file | sha1sum`
	files_info="${files_info}${file},${s}
"
done

echo "$files_info" | awk -F, '{print $2}' | sort | uniq -c | sort -r -n | head -n -1 | awk '$1 > 1 {print $0}' | awk '{print $2}' | while read info; do
	for file in `find $dir -type f`; do
		s=`cat $file | sha1sum`
		if `echo "$s" | grep -E -q "$info"`; then
			echo "$file"
		fi
	done
	echo ""
done


