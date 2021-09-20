#!/bin/bash

echo "Give a number: "
read x
rev=0

while [ "$x" -gt 0 ]; do
	last_digit=`expr $x % 10`
	rev=`expr $rev \* 10 + $last_digit`
	x=`expr $x / 10`
done

echo "$rev"

