#!/bin/bash

s=0
for F in `find $1 -type f -name "*.c"`; do
	N=`grep -E "[^ *$]" $F | wc -l`
	S=`expr $S + $N`
done
echo $S
