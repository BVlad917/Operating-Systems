#!/bin/bash
# This script can only run successfully once. After that, the write permissions for "everyone" for 
# the given files must be changed to their initial state (i.e., those file HAVE write permission 
# for "everyone")

DIR=$1

for FILE in `find $DIR -type f`; do
	ALL_PERMISSIONS=`ls -l $FILE | grep -o -E "^-[rwx-]{9}"`
	WRITE_PERMISSION=`ls -l $FILE | grep -o -E "^-[rwx-]{8}" | grep -o -E "[w-]$"`
	if [ "$WRITE_PERMISSION" = "w" ]; then
		echo "$ALL_PERMISSIONS $FILE"
		chmod o-w "$FILE"
		ALL_PERMISSIONS=`ls -l $FILE | grep -o -E "^-[rwx-]{9}"`
		echo "$ALL_PERMISSIONS $FILE"
	fi
done
