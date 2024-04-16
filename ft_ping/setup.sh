#!/bin/bash

# Import the GPG key for verifying the signature
gpg --keyserver keyserver.ubuntu.com --recv-keys 99415CE1905D0E55A9F88026860B7FBB32F8119D
if [ $? -ne 0 ]; then
    echo "Failed to import GPG key."
    exit 1
fi

# Download inetutils and its signature
wget https://ftp.gnu.org/gnu/inetutils/inetutils-2.0.tar.xz
wget https://ftp.gnu.org/gnu/inetutils/inetutils-2.0.tar.xz.sig

# Verify the signature
gpg --verify inetutils-2.0.tar.xz.sig inetutils-2.0.tar.xz
if [ $? -ne 0 ]; then
    echo "Signature verification failed."
    exit 1
fi

# Install inetutils
tar xf inetutils-2.0.tar.xz
cd inetutils-2.0
./configure
make
sudo make install

# Create a symbolic link for ping2 to ping
export PATH=/usr/local/bin:$PATH

# Cleanup
cd ..
rm -rf inetutils-2.0.tar.xz inetutils-2.0.tar.xz.sig inetutils-2.0

echo "Installation and setup complete."
