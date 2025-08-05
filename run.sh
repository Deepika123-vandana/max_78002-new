#!/bin/bash

set -e

echo "🧹 Cleaning previous build..."
make clean

echo "⚙️ Building firmware..."
make

# Detect board via ttyUSB or ttyACM
PORT=$(ls /dev/ttyUSB* /dev/ttyACM* 2>/dev/null | head -n 1)

if [ -z "$PORT" ]; then
    echo "❌ Board not detected (no /dev/ttyUSB* or /dev/ttyACM* found). Skipping flashing."
    exit 1
else
    echo "✅ Board detected at $PORT"
    echo "🚀 Flashing..."
    make flash.openocd PORT=$PORT
fi
