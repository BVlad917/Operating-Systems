#!/bin/bash

for f in `find -type f`; do
	n=`grep -E "cat" $f | wc -l`
	if [ $n -gt 0 ] && [ "$f" != "./1.sh" ]; then
		echo "$f"
	fi
done
