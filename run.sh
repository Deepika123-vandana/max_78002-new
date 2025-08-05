#!/bin/bash

set -e  # Exit immediately if a command fails

export MAXIM_PATH=/home/admin1/MaximSDK
export PATH=$MAXIM_PATH/Tools/OpenOCD/bin:$PATH
export PATH=$MAXIM_PATH/Tools/GNUTools/bin:$PATH

echo "========== CLEANING BUILD =========="
make clean

echo "========== BUILDING PROJECT =========="
make

if [ -e /dev/ttyUSB0 ]; then
    echo "========== BOARD DETECTED =========="
    echo "Flashing firmware to board..."
    make flash.openocd
else
    echo "⚠️ Board not detected at /dev/ttyUSB0. Skipping flashing."
    exit 1
fi

echo "========== READING SERIAL OUTPUT =========="
# Timestamped log file
LOG_FILE="serial_output_$(date +%Y%m%d_%H%M%S).log"

# Save and print serial output for 10 seconds
timeout 10s cat /dev/ttyUSB0 | tee "$LOG_FILE"

echo "✅ Serial output saved to $LOG_FILE"
