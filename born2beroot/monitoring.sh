#!/bin/bash

ARCH=$(uname -srvmo)
PCPU=$(lscpu | awk '/^Socket\(s\):/ {print $2}')
VCPU=$(nproc --all)
RAM_STATS=($(free --mega | awk '/Mem/ {print $2, $3}'))
RAM_TOTAL=${RAM_STATS[0]}
RAM_USED=${RAM_STATS[1]}
RAM_PERCENTAGE=$(awk -v used="$RAM_USED" -v total="$RAM_TOTAL" 'BEGIN {printf "%.2f%%", used / total * 100}')
DISK_STATS=($(df -h --total | awk '/total/ {print $2, $3}'))
DISK_TOTAL=${DISK_STATS[0]}
DISK_USED=${DISK_STATS[1]}
DISK_PERCENTAGE=$(awk -v used="$DISK_USED" -v total="$DISK_TOTAL" 'BEGIN {printf "%.2f%%", used / total * 100}')
CPU_LOAD=$(vmstat 1 1 | tail -1 | awk '{printf "%.1f%%", 100 - $15}')
LAST_BOOT=$(who -b | awk '{print $3, $4}')
LVM=$(lsblk | awk '{print $6}' | grep -q 'lvm' && echo yes || echo no)
TCP=$(ss -ta | grep ESTAB | wc -l)
USER_LOG=$(who | awk '{print $1}' | sort -u | wc -l)
IP_ADDR=$(hostname -I | awk '{print $1}')
MAC_ADDR=$(ip link show | awk '/link\/ether/ {print $2}')
SUDO_LOG=$(journalctl _COMM=sudo | grep COMMAND | wc -l)

wall "
       ------------------------------------------------
       Architecture    : $ARCH
       Physical CPUs   : $PCPU
       Virtual CPUs    : $VCPU
       Memory Usage    : ${RAM_USED}/${RAM_TOTAL} MB ($RAM_PERCENTAGE)
       Disk Usage      : ${DISK_USED}/${DISK_TOTAL} GB ($DISK_PERCENTAGE)
       CPU Load        : $CPU_LOAD
       Last Boot       : $LAST_BOOT
       LVM use         : $LVM
       TCP Connections : $TCP established
       Users logged    : $USER_LOG
       Network         : $IP_ADDR ($MAC_ADDR)
       Sudo            : $SUDO_LOG commands used
       ------------------------------------------------"
