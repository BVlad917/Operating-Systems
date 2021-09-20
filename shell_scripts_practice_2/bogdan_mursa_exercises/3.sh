#!/bin/bash

DIR=$1

if [ -z $DIR ]; then
	echo "Error: No argument provided." >&2
	exit 1
fi

if [ ! -d $DIR ]; then
	echo "Error: Need a directory as argument." >&2
	exit 1
fi

DIR_STATUS=""
while true; do
	CURRENT_STATUS=""
	for FILE in `find $DIR`; do
		if [ -f $FILE ]; then
			WORDS=`sed -E "s/ /\n/g" $FILE | sed -E "s/\.//g" | tr '\n' ' ' | tr -d '\0'`
			CURRENT_STATUS="$CURRENT_STATUS$WORDS"
		fi
	done
	
	if [ "$DIR_STATUS" = "" ] || [ "$DIR_STATUS" != "$CURRENT_STATUS" ]; then
		if [ "$DIR_STATUS" != "" ]; then
			cat "$DIR_STATUS" | tr ' ' '\n' | while read s; do
				echo "$s"
			done
		fi
		echo "$CURRENT_STATUS"
		echo ""
	fi
	
	DIR_STATUS="$CURRENT_STATUS"
	echo ""
	sleep 2
done
