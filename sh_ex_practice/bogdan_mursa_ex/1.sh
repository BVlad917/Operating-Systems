#!/bin/bash

dir1=$1
dir2=$2
dir3=$3

shift 3

if [ ! -d $dir1 ] || [ ! -d $dir2 ] || [ ! -d $dir3 ]; then
	echo "Invalid directories given." >&2
	exit 1
fi

for file in $@; do
	words=`wc -w $file | cut -d' ' -f1`
	lines=`wc -l $file | cut -d' ' -f1`
	if [ $lines -gt 10 ] && [ $words -gt 5 ]; then
		mv $file $dir1
	elif [ $lines -gt 10 ] && [ $words -lt 5 ]; then
		mv $file $dir2
	else
		mv $file $dir3
	fi	
done
