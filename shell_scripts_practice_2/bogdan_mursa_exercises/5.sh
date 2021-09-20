#!/bin/bash

for NUMBER in $@; do
	DIV=2
	PRIME=1
	while [ $DIV -le `expr $NUMBER / 2` ] && [ ! -z $PRIME ]; do
		if [ `expr $NUMBER % $DIV` -eq 0 ]; then
			PRIME=0
		fi
		DIV=`expr $DIV + 1`
	done
	if [ $NUMBER -eq 1 ] || [ $PRIME -eq 0 ]; then
		echo "The number $NUMBER is NOT prime."
	else
		echo "The number $NUMBER is prime."
	fi
	
done
