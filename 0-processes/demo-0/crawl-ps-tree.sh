#!/bin/bash
set -eu
set -o pipefail


currentPid="$$"
parentPid="${PPID}"


formatOutput(){
	local thisPid=$1
	local parentPid=2

	echo "*  process: ${thisPid}"
	echo "** runs:    $(file /proc/${thisPid}/exe)"
	echo "** cmd:     $(cat /proc/${thisPid}/cmdline | tr -d '\0')"
	echo "** parent:  ${parentPid}"
	echo "*******"
}



formatOutput "${currentPid}" "${parentPid}"
# walk the tree	
for (( ; ; ))
do

	currentPid="${parentPid}"
	if [[ "$currentPid" == "1"  ]]; then
		echo "*  process: ${currentPid}"
		echo "** runs:    $(file /proc/${currentPid}/exe)"
		echo "** cmd:     $(cat /proc/${currentPid}/cmdline | tr -d '\0')"
		echo "** at root, exiting.."
		break
	fi

	parentPid="$(cat /proc/${currentPid}/status | grep PPid | awk '{print $2}')"
	formatOutput "${currentPid}" "${parentPid}"
done


