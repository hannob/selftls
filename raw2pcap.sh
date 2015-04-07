#!/bin/sh
# Author: Hanno Böck
# License: CC0

if [ -z "$2" ]; then
	echo "Convert raw packets to pcap files (used by wireshark, tcpdump etc.)"
	echo ""
	echo "Usage:"
	echo "\traw2pcap.sh [raw input] [pcap output]"
	exit -1
fi

od -Ax -tx1 -v $1 | text2pcap -T 443,443 - $2
