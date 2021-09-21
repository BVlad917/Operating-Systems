#!/bin/bash

DIR=$1
CNT=0

for FILE in `find $DIR -type f -name *.c`; do
	LINE_CNT=`cat $FILE | wc -l`
	if [ $LINE_CNT -gt 500 ]; then
		echo "File $FILE has $LINE_CNT lines."
		CNT=`expr $CNT + 1`
		if [ $CNT -eq 2 ]; then
			break;
		fi
	fi
done
