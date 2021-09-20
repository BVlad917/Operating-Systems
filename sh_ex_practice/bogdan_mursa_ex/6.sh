#!/bin/bash

a=( "$@" )

for ((i=0; i<${#}-1; i++)); do
	for ((j=${i}+1; j<$#; j++)); do
		if [ ${a[$i]} -gt ${a[$j]} ]; then
			temp=${a[$i]}
			a[$i]=${a[$j]}
			a[$j]=$temp
		fi
	done
done

for ((i=0; i<$#; i++)); do
	echo "${a[$i]}"
done
