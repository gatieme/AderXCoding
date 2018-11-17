#!/bin/bash


set -e
br=qemu-gatieme
dev=eth0

ip=$(ip addr show dev $dev | awk '/inet/ {print $2;exit}')


qemu_br_up()
{
	sudo brctl addbr $br
	sudo brctl stp $br on
	sudo ip addr add $ip dev $br
	sudo brctl addif $br $dev
	sudo ip addr del $ip dev $dev
	sudo ip link set $br up
}


qemu_br_down()
{
	sudo brctl delbr $br
}

if [ $1 == "up" ]; then
	qemu_br_up
else
	qemu_br_down
fi
