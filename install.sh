#!/bin/bash

# Build the project
make

# Install the binary to /usr/local/bin
if [ -d "/usr/local/bin" ]; then
    cp bin/sukuna /usr/local/bin/
    echo "sukuna installed successfully!"
else
    echo "/usr/local/bin does not exist. Install failed."
fi
