#! /bin/bash

# Script to change brightness by changing the value in /sys/class/backlight/intel_backlight/brightness

MAX_BRIGHTNESS=`cat /sys/class/backlight/intel_backlight/max_brightness`
CURR_BRIGHTNESS=`cat /sys/class/backlight/intel_backlight/brightness`
STEP=20

case $1 in
	+)
		NEXT_BRIGHTNESS=$(($CURR_BRIGHTNESS+$STEP))

		if [[ $NEXT_BRIGHTNESS -gt $MAX_BRIGHTNESS ]]; then
			NEXT_BRIGHTNESS=$MAX_BRIGHTNESS
		fi

		tee /sys/class/backlight/intel_backlight/brightness <<< $NEXT_BRIGHTNESS
		;;
	-)
		NEXT_BRIGHTNESS=$((CURR_BRIGHTNESS-$STEP))

		if [[ $NEXT_BRIGHTNESS -lt 0 ]]; then
			NEXT_BRIGHTNESS=0
		fi

		tee /sys/class/backlight/intel_backlight/brightness <<< $NEXT_BRIGHTNESS
		;;
	*)
		echo "Usage brightness.sh [+-]"
		;;
esac
