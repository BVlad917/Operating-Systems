#!/bin/bash

if [ $# -eq 0 ]; then
	echo "The program expects numerical input arguments." >&2
	exit 1
fi

for n in $@; do
	if [ $n -le 1 ]; then
		echo "The number $n is NOT prime."
	elif [ $n -eq 2 ]; then
		echo "The number $n is prime."
	elif [ `expr $n % 2` -eq 0 ]; then
		echo "The number $n is NOT prime."
	else
		d=3
		prime=1
		while [ $d -lt `expr $n / 2` ]; do
			if [ `expr $n % $d` -eq 0 ]; then
				echo "The number $n is NOT prime."
				prime=0
				break
			fi
			d=`expr $d + 2`
		done
		if [ $prime -eq 1 ]; then
			echo "The number $n is prime."
		fi
	fi
done
