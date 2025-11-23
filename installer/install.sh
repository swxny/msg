#!/bin/bash

set -e

REPO_URL="https://github.com/swxny/msg"
TMP_DIR=$(mktemp -d)
BINARY_NAME="msg"

echo "Cloning repository..."
git clone "$REPO_URL" "$TMP_DIR"
cd "$TMP_DIR"

if [ -f Makefile ]; then
    echo "Building project using Makefile..."
    make
    BINARY_PATH="build/$BINARY_NAME"
else
    echo "No Makefile found, compiling manually..."
    g++ -std=c++17 -Wall -pthread *.cpp -o $BINARY_NAME `pkg-config --cflags --libs sqlite3 ncurses`
    BINARY_PATH="$BINARY_NAME"
fi

echo "Installing binary..."
sudo cp "$BINARY_PATH" /usr/local/bin/
sudo chmod +x /usr/local/bin/$BINARY_NAME

[ -d /usr/share/bin ] && sudo cp "$BINARY_PATH" /usr/share/bin/

# Create remove_msg binary
REMOVE_BINARY="/usr/local/bin/remove_msg"
sudo tee "$REMOVE_BINARY" > /dev/null << 'EOF'
#!/bin/bash
echo "Removing msg..."
[ -f /usr/local/bin/msg ] && sudo rm -f /usr/local/bin/msg
[ -f /usr/share/bin/msg ] && sudo rm -f /usr/share/bin/msg
echo "msg removed successfully."
EOF
sudo chmod +x "$REMOVE_BINARY"
echo "Uninstall command installed as 'remove_msg' in /usr/local/bin"

echo "Cleaning up..."
rm -rf "$TMP_DIR"

echo "Installation completed! You can run '$BINARY_NAME' from anywhere, and 'remove_msg' to uninstall it."
