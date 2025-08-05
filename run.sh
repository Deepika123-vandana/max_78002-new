make clean
make
if lsusb | grep -q "Maxim Integrated"; then
    echo "Board detected, flashing..."
    make flash.openocd
else
    echo "Board not detected, skipping flashing."
fi
