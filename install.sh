#!/bin/bash
REPO="VivicatcHub/SoundBoardTTY"
BIN_NAME="sbtty"
INSTALL_DIR="/usr/local/bin"

./dependencies.sh

LATEST_RELEASE=$(curl -s https://api.github.com/repos/$REPO/releases/latest | grep "browser_download_url" | cut -d '"' -f 4)
wget -O "$BIN_NAME" "$LATEST_RELEASE"
chmod +x "$BIN_NAME"
sudo mv "$BIN_NAME" "$INSTALL_DIR/$BIN_NAME"

echo "Installation terminée !"
