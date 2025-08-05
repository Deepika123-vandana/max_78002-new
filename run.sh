#!/bin/bash

set -e  # Exit immediately if a command fails

# Add these lines to ensure environment is set for Jenkins
export MAXIM_PATH=/home/admin1/MaximSDK
export PATH=$MAXIM_PATH/Tools/OpenOCD/bin:$PATH
export PATH=$MAXIM_PATH/Tools/GNUTools/bin:$PATH
# Add any other tool paths if needed

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


echo ""
echo "Serial device found at /dev/ttyUSB0"
echo "Launching serial terminal at 115200 baud..."

# Record serial output for 10 seconds only
timeout 10s cat /dev/ttyUSB0 | tee serial_output.log

