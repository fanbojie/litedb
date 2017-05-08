#!/usr/bin/env sh

LD_LIBRARY_PATH=../Lib/Debug
export LD_LIBRARY_PATH
export LC_ALL=zh_CN.gb2312
ulimit -S -c unlimited
ulimit -n 65535
