#!/bin/bash

trap 'kill `jobs -p` &>/dev/null' EXIT SIGINT SIGTERM

CLIENTS=$1
../bin/server $CLIENTS &>/dev/null &

./launch_clients.sh $CLIENTS &>/dev/null


if [ $? -ne 0 ]; then
  exit 1
fi

kill %1


exit 0

