#!/bin/bash

dir=$1

for file in `ls "$1"/*`; do
	echo "$file"
done
