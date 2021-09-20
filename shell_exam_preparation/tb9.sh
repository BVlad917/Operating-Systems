#!/bin/bash

file=$1
new_text=""
nl=$'\n'

while read line; do
	text=`echo "$line" | grep -E -v "^(\<[^ ]+\> +){4,6}dd"`
	if [ ! "$text" == "" ]; then
		new_text="${new_text}${text}${nl}"
	fi
done < "$file"

echo "${new_text}" > "$file"
