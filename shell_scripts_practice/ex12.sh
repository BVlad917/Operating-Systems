#!/bin/bash

function file_count()
{
	local NUMBER_OF_FILES=`ls -l | wc -l`
	echo "$NUMBER_OF_FILES"
}

file_count
