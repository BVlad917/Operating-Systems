#!/bin/bash

FILE="/home/vbie3041/hello.sh"

if [ -f $FILE ]; then
	echo "$FILE passwords are enabled."
fi

if [ -w $FILE ]; then
	echo "You have permissions to edit $FILE."
else
	echo "You do NOT have permissions to edit $FILE."
fi
