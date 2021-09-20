#!/bin/bash

DIR=$1

for FILE in `find $DIR`; do
	if [ -L FILE ] && [ ! -e FILE ]; then
		echo "The file $FILE no longer exists."
	fi
done
