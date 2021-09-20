#!/bin/bash

NUMBER=$1
PATTERN=$2

if [ -z $NUMBER ] || [ -z $PATTERN ]; then
	echo "ERROR: The program expects 2 arguments." >&2
fi

if [ $PATTERN -eq 1 ]; then
	INDEX=1
	while [ $INDEX -le $NUMBER ]; do
		SPACES=1
		HASHTAGS=1
		LINE=""

		while [ $SPACES -le `expr $NUMBER - $INDEX` ]; do
			LINE="$LINE "
			SPACES=`expr $SPACES + 1`	
		done
		
		while [ $HASHTAGS -le $INDEX ]; do
			LINE="${LINE}#"
			HASHTAGS=`expr $HASHTAGS + 1`
		done

		echo "$LINE"
		INDEX=`expr $INDEX + 1`
	done
elif [ $PATTERN -eq 2 ]; then
	INDEX=1
	TOTAL_CHARS=`expr 2 \* $NUMBER - 1 + 2 + 2`
	while [ $INDEX -le $NUMBER ]; do
		SPACES=1
		HASHTAGS=1
		LINE=""
		NR_HASHTAGS=`expr 2 \* $INDEX - 1`
		NR_SPACES=`expr $TOTAL_CHARS - $NR_HASHTAGS`
		NR_SPACES=`expr $NR_SPACES / 2`
		
		while [ $SPACES -le $NR_SPACES ]; do
			LINE="$LINE "
			SPACES=`expr $SPACES + 1`
		done

		while [ $HASHTAGS -le $NR_HASHTAGS ]; do
			LINE="${LINE}#"
			HASHTAGS=`expr $HASHTAGS + 1`
		done

		SPACES=1
		while [ $SPACES -le $NR_SPACES ]; do
			LINE="$LINE "
			SPACES=`expr $SPACES + 1`
		done

		echo "$LINE"
		INDEX=`expr $INDEX + 1`

	done
fi
