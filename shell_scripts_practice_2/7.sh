#!/bin/bash

file=$1
str=""

while read username; do
	email="${username}@scs.ubbcluj.ro"
	str="${str}${email},"
done < "$file"

str=`echo "$str" | sed -E s/,$//`

echo "$str"
