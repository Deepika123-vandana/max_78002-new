#!/bin/bash

set -e  # Exit immediately if a command fails

# Set environment paths for Jenkins
export MAXIM_PATH=/home/admin1/MaximSDK
export PATH=$MAXIM_PATH/Tools/OpenOCD/bin:$PATH
export PATH=$MAXIM_PATH/Tools/GNUTools/bin:$PATH

echo "=== Cleaning project ==="
make clean

echo "=== Building project ==="
make

# Flash if board is connected
if [ -e /dev/ttyUSB0 ]; then
    echo "=== Board connected at /dev/ttyUSB0 ==="
    echo "=== Flashing firmware ==="
    make flash.openocd
else
    echo "=== Board not detected at /dev/ttyUSB0, skipping flashing ==="
fi

# Serial logging
LOG_FILE="serial_output.log"
echo "=== Starting serial log capture ==="

# Using background process to read from serial
# Flush previous content
> $LOG_FILE

# Background capture from serial
timeout 15s cat /dev/ttyUSB0 | tee $LOG_FILE &
CAPTURE_PID=$!

# Optional delay for board to boot and print
sleep 2

# Wait for capture to finish
wait $CAPTURE_PID

echo "=== Serial log captured ==="
echo "=== Output Start ==="
cat $LOG_FILE
echo "=== Output End ==="



# Check for known failure pattern
if grep -q "FAILED" serial_output.log; then
    echo "Error detected in serial output!"
    exit 1
else
    echo "No errors found in serial output."
fi
