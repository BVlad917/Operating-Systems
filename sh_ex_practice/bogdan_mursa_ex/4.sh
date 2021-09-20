#!/bin/bash

file=$1

if [ -z $file ] || [ ! -f $file ]; then
	echo "Invalid argument given." >&2
	exit 1
fi

content=`cat $file`
echo "$content" | sed -E "s/ /\n/g" | sort > $file
