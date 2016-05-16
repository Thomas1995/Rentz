#!/bin/bash

pushd ../bin

trap 'kill $(jobs -p)' EXIT

for i in `seq 1 $1`; do
  ./client &>/dev/null &
done

for i in `seq 1 $1`; do
  wait %"$i"
done

popd
