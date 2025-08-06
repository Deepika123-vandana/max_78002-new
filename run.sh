#!/bin/bash

set -e

echo "=== Starting serial log capture ==="
# Start minicom or cat depending on your setup
timeout 10s cat /dev/ttyUSB0 | tee serial_output.log

echo "=== Serial log captured ==="
echo -e "\n=== Output Start ==="
cat serial_output.log
echo "=== Output End ==="

# Fail the script if "FAILED" is found in the log
if grep -q "FAILED" serial_output.log; then
    echo "Detected FAILURE in serial output"
    exit 1
else
    echo "Test output looks good"
fi
