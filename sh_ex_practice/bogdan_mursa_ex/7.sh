#!/bin/bash

number=$1
pattern=$2

if [ -z $number ] || [ -z $pattern ]; then
	echo "Invalid parameters given." >&2
	exit 1
fi

if [ $pattern -eq 1 ]; then
	hashtags=1
	spaces=`expr $number - 1`
	while [ $hashtags -le $number ]; do
		line=""
		i=1
		while [ $i -le $spaces ]; do
			line="$line "
			i=`expr $i + 1`
		done
		i=1
		while [ $i -le $hashtags ]; do
			line="${line}#"
			i=`expr $i + 1`
		done
		echo "$line"
		hashtags=`expr $hashtags + 1`
		spaces=`expr $spaces - 1`
	done
elif [ $pattern -eq 2 ]; then
	hashtags=1
	spaces=`expr $number + 1`
	while [ $hashtags -le `expr $number \* 2 - 1` ]; do
		line=""
		i=1
		while [ $i -le $spaces ]; do
			line="$line "
			i=`expr $i + 1`
		done
		i=1
		while [ $i -le $hashtags ]; do
			line="${line}#"
			i=`expr $i + 1`
		done
		echo "$line"
		hashtags=`expr $hashtags + 2`
		spaces=`expr $spaces - 1`
	done
else
	echo "Invalid pattern number given." >&2
	exit 1
fi
