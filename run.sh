#!/bin/bash

# Build the project
echo "===== Building the project ====="
make clean && make

# Find the generated ELF file (modify the pattern if needed)
ELF_FILE=$(find . -name "*.elf" | head -n 1)

if [[ ! -f "$ELF_FILE" ]]; then
    echo "ELF file not found!"
    exit 1
fi

# Flash the ELF file (replace with actual OpenOCD/GDB commands if needed)
echo "===== Flashing $ELF_FILE ====="
# Add your real flashing logic here, placeholder:
# openocd -f interface.cfg -c "program $ELF_FILE verify reset exit"

sleep 2  # Optional delay

# Capture UART output into a log file (simulate or replace with actual minicom/pyserial/etc.)
echo "===== Capturing serial output ====="
echo "=== Starting serial log capture ===" > serial_output.log
# Example simulated output
echo "Test cases of GPIO FAILED!" >> serial_output.log
echo "=== Serial log captured ===" >> serial_output.log
