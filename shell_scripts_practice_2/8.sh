#!/bin/bash

cat df.fake | tail +2 | while read info; do
	size=`echo "$info" | awk '{print $2}' | sed -E "s/G//" | sed -E "s/M//"`
	use=`echo "$info" | awk '{print $5}' | sed -E "s/%//"`
	if [ $size -lt 1024 ] || [ `expr 100 - $use` -lt 20 ]; then
		echo "$info" | awk '{print $6}'
	fi
done
