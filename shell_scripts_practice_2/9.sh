#!/bin/bash

dir=$1
info=""

for file in `find $dir -type f`; do
	file_info=`cat $file | sha1sum`
	info="${info}${file},${file_info}
"
done

echo "$info" | awk -F, '{print $2}' | sort | uniq -c | sort -n -r | awk '$1 > 1 {print $0}' | awk '{print $2}' | while read check_sum; do
	for file in `find $dir -type f`; do
		file_info=`cat $file | sha1sum`
		if [[ `echo "$file_info" | grep "$check_sum"` ]]; then
			echo "$file"
		fi
	done
	echo ""
done
