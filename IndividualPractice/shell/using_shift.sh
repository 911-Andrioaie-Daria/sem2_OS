#!/bin/sh

echo Command: $0
echo First four args: $1 $2 $3 $4
echo All args: $@
echo Arg count: $#
echo

#true
#echo Command true exited with code $?

#false
#echo Command false exited with code $?

shift
echo Some args: $1 $2 $3 $4
echo All args: $@
echo Arg count: $#
echo

shift 3
echo Some args: $1 $2 $3 $4
echo All args: $@
echo Arg count: $#
echo

