#!/bin/bash

#while read file; do
#	echo "$file"
#done < <(ps)

cat df.fake | tail -n +2 | while read file; do
	size=`echo $file | awk '{print $2}' | sed -E "s/M//"`
	used=`echo $file | awk '{print $5}' | sed -E "s/%//"`
	path=`echo $file | awk '{print $6}'`
	if [ $size -lt 1024 ] || [ $used -gt 80 ]; then
		echo "$path"
	fi
done
