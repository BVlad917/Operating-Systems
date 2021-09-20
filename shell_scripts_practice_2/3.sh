#!/bin/bash

DIR=$1

for FILE in `find $DIR -type f -name *.log`; do
	sort $FILE > tmp
	mv tmp $FILE
done
