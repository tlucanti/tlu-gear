#!/bin/bash

echoerr() { echo "$@" 1>&2; }

for func in $@ ; do
	if [ -f generic-fast/$func ] ; then
		echo generic-fast/$func
	elif [ -f generic-slow/$func ] ; then
		echo generic-slow/$func
	else
		echoerr "NO SOURCE FILE FOUND FOR FUNCTION $func"
	fi
done
