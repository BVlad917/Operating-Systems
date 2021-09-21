#!/bin/bash

#echo "Please enter the name of the file: "
#read FILE

for FILE in $@; do
	if [ -f $FILE ]; then
		echo "$FILE is a regular file."
		echo "`ls -l $FILE`"
	elif [ -d $FILE ]; then
		echo "$FILE is a directory."
		echo "`ls -l -d $FILE`"
	else
		echo "$FILE is neither a file, nor a directory."
	fi
	echo ""
done
