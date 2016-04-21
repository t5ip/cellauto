#!/bin/bash

r=107
while [ 1 ]; do
    echo "rule "$r
    ./cellauto $r&
    sleep 2
    r=$(($r+1))
    killall cellauto
done
