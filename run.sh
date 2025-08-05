#!/bin/bash

# Exit immediately if any command fails
set -e

# 1. Export SDK path
export MAXIM_PATH=/home/admin1/MaximSDK
export PATH=$MAXIM_PATH/tools/openocd/bin:$MAXIM_PATH/tools/gcc-arm-none-eabi/bin:$PATH

# 2. Run Makefile
make clean
make

# 3. Find the generated ELF file
ELF_FILE=$(find . -type f -name "*.elf" | head -n 1)

if [ -z "$ELF_FILE" ]; then
    echo "❌ ELF file not found after build"
    exit 1
fi

echo "✅ ELF File Found: $ELF_FILE"

# 4. Flash using OpenOCD
openocd -f $MAXIM_PATH/tools/OpenOCD/max32655/max32655.cfg -c "program $ELF_FILE verify reset exit"

# 5. Detect serial port (modify if needed)
SERIAL_PORT="/dev/ttyUSB0"
BAUD_RATE=115200

# 6. Create log file to store serial output
LOG_FILE="serial_output_$(date +%Y%m%d_%H%M%S).log"

# 7. Launch serial terminal and log output
echo "📡 Launching serial terminal at $SERIAL_PORT ($BAUD_RATE)..."
cat $SERIAL_PORT > "$LOG_FILE" &

SERIAL_PID=$!

# Wait some time to collect data
sleep 10

# Kill the serial logging after 10s (or adjust as needed)
kill $SERIAL_PID

# 8. Send log output via email (requires `mailx` configured)
TO_EMAIL="your_email@example.com"
SUBJECT="Maxim ELF Output Log"
cat "$LOG_FILE" | mailx -s "$SUBJECT" "$TO_EMAIL"

echo "📬 Serial log sent to $TO_EMAIL"
