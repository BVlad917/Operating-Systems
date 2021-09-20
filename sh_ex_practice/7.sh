#!/bin/bash

dir=$1
emails=""

while read u; do
	e="$u@scs.ubbcluj.ro"
	emails="${emails},${e}"
done < $dir

emails=`echo "$emails" | sed -E "s/^,//"`
echo "$emails"
