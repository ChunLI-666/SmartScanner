#!/bin/bash

# Livox SDK2 Installation Script
# This script installs the Livox SDK2 library to the system

set -e

echo "Installing Livox SDK2..."
cd /home/pi/navinet_locmap/SmartScanner/deviceDrivers/sdks/Livox-SDK2/build

# Install the library
sudo make install

# Update library cache
sudo ldconfig

echo ""
echo "Livox SDK2 installed successfully!"
echo ""
echo "Installed files:"
echo "  - Libraries: /usr/local/lib/liblivox_lidar_sdk_*"
echo "  - Headers: /usr/local/include/livox_*"
echo ""
echo "You can now rebuild the mid360_driver package with:"
echo "  cd /home/pi/navinet_locmap"
echo "  colcon build --packages-select mid360_driver"

