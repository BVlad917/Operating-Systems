#!/bin/bash

dir=$1

for file in `find $dir -type f`; do
	permissions=`ls -l $file | awk '{print $1}'`
	path=`ls -l $file | awk '{print $9}'`
	if `echo "$permissions" | grep -E -q "^-[rwx-]{7}w"`; then
		echo "${permissions} ${path}"
		chmod o-w "$path"
		permissions=`ls -l $file | awk '{print $1}'`
		echo "${permissions} ${path}"
	fi
done
