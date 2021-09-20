#!/bin/bash

file=$1

sed -E -i "/ff2/d" $file
sed -E -i "/^[ ]*$/d" $file
