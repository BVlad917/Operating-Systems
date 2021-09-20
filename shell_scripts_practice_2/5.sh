#!/bin/bash

while true; do
	for PROGRAM in $@; do
		cat ps.fake | grep -E "$PROGRAM" | awk '{print $2}' | while read PID; do
			echo "Will kill the process with PID $PID"
			kill -9 "$PID":
		done
	done
	sleep 2
done
