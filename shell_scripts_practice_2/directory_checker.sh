#!/bin/bash

D=$1
if [ -z "$D" ]; then
	echo "ERROR: No directory provided for monitoring" >&2
	exit 1
fi
if [ ! -d "$D" ]; then
	echo "ERROR: Directory $D does not exist" >&2
	exit 1
fi

f_status=""
while true; do
	current_status=""
	for A in `find $D`; do
		if [ -f $A ]; then
			details=`ls -l $A | sha1sum`
			content_details=`cat $A | sha1sum`
		elif [ -d $A ]; then
			details=`ls -l -d $A | sha1sum`
			content_details=`ls -l $A | sha1sum`
		fi
		current_status="$current_status \n $details $content_details"
	done
	if [ "$f_status" != "" ] && [ "$f_status" != "$current_status" ]; then
		echo "Changed"
	fi
	f_status=$current_status
	sleep 2
done
