#!/bin/bash

FIRST=${1:-0}
INCR=${2:-1}
LAST=${3:-10}

echo -e "TEST DATA INFO: from $FIRST to $LAST, increment is $INCR\n"

./test $(seq $FIRST $INCR $LAST)
