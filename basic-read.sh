#!/bin/bash

F=""
while test -z "$F" || test ! -f "$F" || test ! -r "$F"; do
	read -p "Provide an existing and readable file path: " F
done
