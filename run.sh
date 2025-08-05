#!/bin/bash

# Step 1: Build
echo "Cleaning and building..."
make clean
make

# Step 2: Check for Maxim Integrated board and flash
if lsusb | grep -q "Maxim Integrated"; then
    echo "Board detected, flashing..."
    make flash.openocd
else
    echo "Board not detected, skipping flashing."
fi

# Step 3: Check for /dev/ttyUSB0
PORT="/dev/ttyUSB0"
if [ -e "$PORT" ]; then
    echo "Serial device found at $PORT"
    echo "Launching serial terminal at 115200 baud..."
    
    # Install minicom if not already present
    if ! command -v minicom &> /dev/null; then
        echo "minicom not found, installing..."
        sudo apt update && sudo apt install -y minicom
    fi

    # Launch minicom
    sudo minicom -D $PORT -b 115200
else
    echo "Serial port $PORT not found. CLI not launched."
fi
