#!/bin/bash

nowDateTime(){
	date +"  %Y/%m/%d   %H:%M  "
}

isConnectWifi(){
	if iwctl station list | grep -wq connected; then
		echo "  直  `iwctl station wlan0 show | grep "Connected network" | awk '{for(i=3;i<=NF;++i)printf $i" "}' ` "
	else
		echo "  睊  "
	fi
}

outputChargingIcon(){
	case $(( $1 / 10 )) in
	[0-2])
		echo ""
	;;
	3)
		echo ""
	;;
	[4-5])
		echo ""
	;;
	[6-7])
		echo ""
	;;
	8)
		echo ""
	;;
	9)
		echo ""
	;;
	10)
		echo ""
	;;
	esac
}

outputDisChargingIcon(){
	case $(( $1 / 10 )) in
	0)
		echo ""
	;;
	1)
		echo ""
	;;
	2)
		echo ""
	;;
	3)
		echo ""
	;;
	4)
		echo ""
	;;
	5)
		echo ""
	;;
	6)
		echo ""
	;;
	7)
		echo ""
	;;
	8)
		echo ""
	;;
	9)
		echo ""
	;;
	10)
		echo ""
	;;
	esac
}

batteryStatus(){
	battery_status_line=`acpi | grep "Battery 0"`
	if [ -n "$battery_status_line" ]; then
		charging_status=`echo $battery_status_line | awk -F'[, ]' '{print $3}'`
		battery=`echo $battery_status_line | sed -r 's/.* (.*)%.*/\1/'`
		if [ "$charging_status" = "Discharging" ]; then
			echo "  `outputDisChargingIcon $battery`  $battery%  "
		elif [ "$charging_status" = "Charging" ]; then
			echo "  `outputChargingIcon $battery`  $battery%  "
		fi
	fi


}

outputVolumeIcon(){
	if [ $1 -eq 0 ]; then
		echo "奄"
	elif [ $1 -lt 50 ]; then
		echo "奔"
	else
		echo "墳"
	fi
}

outputVolume(){
        volume_line=`amixer get Master | tail -n1`
	volume=`echo $volume_line | sed -r 's/.*\[(.*)%\].*/\1/'`
	volume_status=`echo $volume_line | awk '{print $6}' | sed -r 's/\[(.*)\]/\1/'`
        if [ $volume_status = "on" ]; then
                echo -e "`outputVolumeIcon $volume`  $volume%"
        else
                echo -e "婢  $volume%"
        fi
}

xsetroot -name "  `isConnectWifi` `outputVolume` `batteryStatus` `nowDateTime`  "
#echo "  `isConnectWifi``batteryStatus``nowDateTime`  "

