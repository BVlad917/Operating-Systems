#!/bin/bash

TODAY=$(date +%F)

echo "Please enter the file extension: "
read EXTENSION

echo "Please enter the prefix(leave empty to have today as prefix): "
read PREFIX

for FILE in *.$EXTENSION; do
	if [ -z $PREFIX ]; then
		echo "Renaming $FILE to $TODAY-$FILE"
		mv $FILE $TODAY-$NAME
	else
		echo "Renaming $FILE to $PREFIX-$FILE"
		mv $FILE $PREFIX-$FILE
	fi
done
