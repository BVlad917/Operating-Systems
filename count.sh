#!/bin/bash

s=0
for F in $1/*.c; do
	N=`grep -E "[^ *$]" $F | wc -l`
	S=`expr $S + $N`
done
echo $S
