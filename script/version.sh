#!/bin/bash

SCRIPT_PATH="$(dirname "$(readlink -f $0)")"
PROJECT_PATH="$(dirname "$SCRIPT_PATH")"
SOURCE_PATH=$SCRIPT_PATH/version.cpp.in
TARGET_PATH=$PROJECT_PATH/src/guutil/version.cpp

HASH_KEY='HASH'
HASH_VAL=`git rev-parse --short HEAD`

UPDATED_KEY='UPDATED'
UPDATED_VAL=`git log -1 --date=format:"%Y/%m/%d %T" --pretty=format:%ad`
UPDATED_CHANGE=$(echo $UPDATED_VAL $i | sed -e 's/\//\\\//g')

if [ -d $TARGET_PATH ]; then
    rm $TARGET_PATH
fi

sed "s/$HASH_KEY/$HASH_VAL/g" $SOURCE_PATH | sed "s/$UPDATED_KEY/$UPDATED_CHANGE/g" > $TARGET_PATH 

echo update revision $HASH_VAL "($UPDATED_VAL)"
