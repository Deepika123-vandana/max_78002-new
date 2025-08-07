#!/bin/bash

set -e  # Stop on first error

export MAXIM_PATH=/home/admin1/MaximSDK
export PATH=$MAXIM_PATH/Tools/OpenOCD/bin:$PATH
export PATH=$MAXIM_PATH/Tools/GNUTools/bin:$PATH

echo "=== Flashing firmware ==="
make flash.openocd

echo "=== Waiting for device to boot ==="
sleep 2

echo "=== Starting serial capture ==="

# Setup serial port
stty -F /dev/ttyUSB0 115200 raw -echo

# Capture serial for 20 seconds
timeout 20s cat /dev/ttyUSB0 > serial_output.log

echo "=== Serial capture complete ==="
cat serial_output.log
