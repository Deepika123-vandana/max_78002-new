

set -e

export MAXIM_PATH=/home/admin1/MaximSDK
export PATH=$MAXIM_PATH/Tools/OpenOCD/bin:$PATH
export PATH=$MAXIM_PATH/Tools/GNUTools/bin:$PATH

SERIAL_PORT="/dev/ttyUSB0"
LOG_FILE="serial_output.log"

# Ensure log file is fresh
> $LOG_FILE

echo "=== Configuring serial port ==="
stty -F $SERIAL_PORT 115200 raw -echo

echo "=== Starting background serial log capture ==="
# Start listening to serial before flashing (to catch early boot prints)
cat $SERIAL_PORT > $LOG_FILE &
CAPTURE_PID=$!

sleep 1

echo "=== Flashing firmware ==="
make flash.openocd

# Wait for board to boot and send prints
echo "=== Waiting for board to boot and send prints... ==="
sleep 10

# Kill capture after 10s
kill $CAPTURE_PID 2>/dev/null || true

echo "=== Serial capture complete ==="
echo "=== Output Start ==="
cat $LOG_FILE
echo "=== Output End ==="

# Check for error pattern in serial output
if grep -q "FAILED" "$LOG_FILE"; then
    echo "Error detected in serial output!"
    exit 1
else
    echo "No errors found in serial output."
fi
