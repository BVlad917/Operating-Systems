#!/bin/bash

DIRECTORY=$1

echo "$DIRECTORY: "
echo "`ls $DIRECTORY | wc -l`"

