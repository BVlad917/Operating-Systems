#!/bin/bash

a=("$@")
a_len=$#

swapped=1
while [ $swapped -ne 0 ]; do
	swapped=0
	for ((i=0; i<${a_len}-1; i++)); do
		if [ ${a[$i]} -gt ${a[${i}+1]} ]; then
			temp=${a[$i]}
			a[$i]=${a[${i}+1]}
			a[${i}+1]=$temp
			swapped=1
		fi
	done
done

for ((i=0; i<$a_len; i++)); do
	echo "${a[$i]}"
done
