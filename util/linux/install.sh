#!/bin/bash

# Install the binary
INSTALL_DIR="/usr/local/bin"
BINARY="sukuna"

# Check if the script is run as root
if [ "$(id -u)" -ne "0" ]; then
  echo "This script must be run as root. Use 'sudo' to execute."
  exit 1
fi

# Copy binary to installation directory
cp "$BINARY" "$INSTALL_DIR/"

# Verify installation
if [ -f "$INSTALL_DIR/$BINARY" ]; then
  echo "Installation successful. You can now run '$BINARY' from anywhere."
else
  echo "Installation failed."
fi
