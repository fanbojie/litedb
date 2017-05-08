#!/bin/bash

# <1> Set Build Target

SP_TARGETS[1]="linux32-centos6-gcc-debug"
SP_TARGETS[2]="linux32-centos6-gcc-release"
SP_TARGETS[3]="linux64-centos6-gcc-debug"
SP_TARGETS[4]="linux64-centos6-gcc-release"
SP_TARGETS[5]="linux32-centos5-gcc-debug"
SP_TARGETS[6]="linux32-centos5-gcc-release"
SP_TARGETS[7]="mac32-llvmgcc42-debug"
SP_TARGETS[8]="mac32-llvmgcc42-release"
SP_TARGETS[9]="linux64-centos5-gcc-debug"
SP_TARGETS[10]="linux64-centos5-gcc-release"
SP_TARGETS_NUM=10

TARGET_TYPE=$1
if [ -z "$TARGET_TYPE" ] ; then
	for (( i = 1 ; i <= $SP_TARGETS_NUM ; i++ )) ; do
		echo "$i : ${SP_TARGETS[$i]}"
	done
	echo "Please choose target :"
	read idx
	TARGET_TYPE=${SP_TARGETS[$idx]}
	if [ -z "$TARGET_TYPE" ] ; then
		echo "ERR : bad choose"
		exit 1
	fi
fi

valid=0
for (( i = 1 ; i <= $SP_TARGETS_NUM ; i++ )) ; do
	if [ "$TARGET_TYPE" == "${SP_TARGETS[$i]}" ] ; then
		valid=1
	fi
done
if [ "$valid" == "0" ] ; then
	echo "Usage: build_pkg.sh <target_type>"
	exit 1
fi

set -x

BUILD_OPT=""
FN_D=""
if [ ${TARGET_TYPE:(-5)} == "debug" ] ; then
	BUILD_OPT="$BUILD_OPT DEBUG=1"
	FN_D="_d"
fi
if [ ${TARGET_TYPE:0:3} == "mac" ] ; then
	BUILD_OPT="$BUILD_OPT MAC=1"
fi

if [ ${TARGET_TYPE:0:7} != "linux64" ] ; then
	BUILD_OPT="$BUILD_OPT M32=1"
fi

# <2> Start build

export LC_ALL=C

echo build at $(date)

make -C .. clean $BUILD_OPT
make -C .. $BUILD_OPT
if [ $? -ne 0 ] ; then
	echo "ERR : build failed"
	exit 1
fi

