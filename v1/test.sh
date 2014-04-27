#!/bin/bash

FIRST=${1:-0}
INCR=${2:-1}
LAST=${3:-10}

echo -e "TEST DATA INFO: from $FIRST to $LAST, increment is $INCR\n"

a=""; for i in $(seq $FIRST $INCR $LAST); do a="$a $i";done;./test $a
