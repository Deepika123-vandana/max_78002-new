#!/bin/bash

set -e

echo "=== Starting serial log capture ==="
minicom -D /dev/ttyUSB0 -b 115200 -C serial_output.log -o -t vt102 &
MINICOM_PID=$!

# Wait for minicom to capture output (adjust as needed)
sleep 10

kill $MINICOM_PID
wait $MINICOM_PID 2>/dev/null || true
echo "=== Serial log captured ==="

echo -e "\n=== Output Start ==="
cat serial_output.log
echo "=== Output End ==="

# Optional: copy for Jenkins artifacts if needed
cp serial_output.log output.log

# Check for known failure pattern
if grep -q "FAILED" serial_output.log; then
    echo "Error detected in serial output!"
    exit 1
else
    echo "No errors found in serial output."
fi
