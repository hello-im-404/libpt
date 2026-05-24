#!/bin/bash
echo "[*] Starting build via Makefile..."
make all

echo -n "Do you want to install libpt to system directories (/usr/local)? [y/N] "
read -r choice

if [[ "$choice" =~ ^[yY]$ ]]; then
    sudo make install
else
    echo "[+] Local build is complete in the 'out/' folder."
fi
