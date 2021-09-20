#!/bin/bash

f=$1
n=0

while [ $n -lt 200 ]; do
	k=`cat $f`
	k=`expr $k + 1`
	echo "$k" > $f
	n=`expr $n + 1`
done
