#!/bin/bash

result=`ps ax | grep -v "grep" | grep "/usr/bin/screenkey"`
if [ -z "$result" ]; then
	screenkey &
else
	killall screenkey
fi
