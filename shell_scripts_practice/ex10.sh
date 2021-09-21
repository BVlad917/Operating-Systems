#!/bin/bash

FILE=$1

if [ -f $FILE ]; then
	echo "$FILE is a regular file. Program exits with exit code 0."
	exit 0
elif [ -d $FILE ]; then
	echo "$FILE is a directory. Program exits with exit code 1."
	exit 1
else
	echo "$FILE is neither a regular file, nor a directoy. Program exits with exit code 2."
	exit 2
fi
