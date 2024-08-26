#!/bin/bash

# Launch gnome-terminal and capture its PID
gnome-terminal -- bash --posix &
BASH_PID=$!

# Wait for a short period to ensure the terminal opens
sleep 2

# Use xdotool to find the window ID of the terminal using its PID
BASH_WINDOW_ID=$(xdotool search --pid $BASH_PID)

# Output the PID and window ID for debugging
echo "Bash PID: $BASH_PID"
echo "Bash Window ID: $BASH_WINDOW_ID"

# Return the window ID as an exit code (optional)
exit $BASH_WINDOW_ID
