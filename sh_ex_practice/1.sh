#!/bin/bash

while read u; do
	name=`echo $u | grep -E -o "^[^ ]+"`
	count=0
	while read m; do
		ps_name=`echo $m | grep -E -o "^[^ ]+ "`
		if `echo "$ps_name" | grep -E -q "$name"`; then
			#echo "$name"
			count=`expr $count + 1`
		fi
	done < `echo ps.fake`
	echo "$name, $count"
done < `echo who.fake`
