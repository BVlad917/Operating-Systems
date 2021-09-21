#!/bin/bash

cat /etc/shadow

if [ $? == 0 ]; then
	echo "Command succeded."
	exit 0
else
	echo "Command failed."
	exit 1
fi
