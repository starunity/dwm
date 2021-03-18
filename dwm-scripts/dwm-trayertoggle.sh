#!/bin/bash

result=`ps ax | grep -v "grep" | grep " trayer "`
if [ -z "$result" ]; then
	trayer --transparent true --edge top --expand false --align right --width 9 --height 39 --tint 0xcc444444 &
else
	killall trayer
fi
