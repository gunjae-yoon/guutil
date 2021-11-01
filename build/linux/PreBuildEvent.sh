#!/bin/bash

LINUX_VER=`uname -r | cut -f 1 -d '.'`
GCC_VER=`gcc --version | grep gcc | rev | cut -f 1 -d ' ' | rev`
BIT=`getconf LONG_BIT`
BUILD_TARGET=x$BIT'Linux'$LINUX_VER'gcc'$GCC_VER

MK_HOME=$PWD
SOL_HOME=$PWD/../..
TARGET_PATH=$SOL_HOME/lib/$BUILD_TARGET

if [ ! -d $TARGET_PATH ]; then
	mkdir -p $TARGET_PATH
fi

WCREV_KEY='\$WCREV\$'
WCREV_VAL=`git rev-parse --short HEAD`
WCDATE_KEY='\$WCDATE\$'
WCDATE_VAL=`git log -1 --date=format:"%Y/%m/%d %T" --pretty=format:%ad`
WCDATE_CHANGE=$(echo $WCDATE_VAL $i | sed -e 's/\//\\\//g')

if [ -d $SOL_HOME/include/guutil/version.h ]
then rm $SOL_HOME/include/guutil/version.h
fi

sed "s/$WCREV_KEY/$WCREV_VAL/g" ../version.h.in | sed "s/$WCDATE_KEY/$WCDATE_CHANGE/g" > $SOL_HOME/include/guutil/version.h

echo update revision $WCREV_VAL "($WCDATE_VAL)"
