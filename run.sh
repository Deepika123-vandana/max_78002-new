#!/bin/bash

set -e  # Exit immediately if a command fails

echo "Running make clean..."
make clean

echo "Building project..."
make

# Check if serial device exists
if [ -e /dev/ttyUSB0 ]; then
    echo "Board connected at /dev/ttyUSB0"
    echo "Flashing firmware..."
    make flash.openocd
else
    echo "Board not detected at /dev/ttyUSB0, skipping flashing."
fi

# Serial log at 115200
echo ""
echo "Serial device found at /dev/ttyUSB0"
echo "Launching serial terminal at 115200 baud..."

# Use cat for non-interactive terminal logging (safe for Jenkins)
cat /dev/ttyUSB0 | tee serial_output.log
