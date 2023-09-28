#!/bin/bash

K="\e[1;30m"
R="\e[1;31m"
G="\e[1;32m"
Y="\e[1;33m"
B="\e[1;34m"
P="\e[1;35m"
C="\e[1;36m"
W="\e[1;37m"
S="\e[0m"

echoerr() { printf "$@\n" 1>&2; }

for func in $@ ; do
	if [ -f generic-fast/$func.c ] ; then
		echoerr "${G}found ${C}generic-fast ${P}${func}${S}"
		echo generic-fast/$func.c
	elif [ -f generic-slow/$func.c ] ; then
		echoerr "${G}found ${C}generic ${P}${func}${S}"
		echo generic-slow/$func.c
	else
		echoerr "$R NO SOURCE FILE FOUND FOR FUNCTION $P$func$S"
	fi
done
