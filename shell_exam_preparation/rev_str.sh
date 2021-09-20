#!/bin/bash

str=$@
rev=""

i=$#

while [ $i -gt 0 ]; do
	word=`echo "$str" | sed -E "s/ /,/g" | cut -d, -f $i`
	rev="${rev}${word}
"
	i=`expr $i - 1`
done

echo "$rev" | sed -E "/^[ ]*$/d"
