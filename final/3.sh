#!/bin/bash

count=0
sum=0

for dir in `find . -type d`; do
	nr=`find $dir -maxdepth 1 -type f -name "*.txt" | wc -l`
	sum=`expr $sum + $nr`	
	count=`expr $count + 1`
	echo "$dir, $nr"
done

avg=`expr $sum / $count`
echo "Average: $avg"
