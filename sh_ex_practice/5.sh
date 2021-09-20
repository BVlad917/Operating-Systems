#!/bin/bash

while true; do
	for program in $@; do
		while read ps_info; do
			if `echo "$ps_info" | grep -E -q "$program"`; then
				pid=`echo "$ps_info" | awk '{print $2}'`
				echo "Will kill the process with PID $pid."
			fi
		done < ps.fake
	done
	sleep 2
done
