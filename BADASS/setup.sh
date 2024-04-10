#!/bin/bash

echo "Starting setup..."

# Exit script on error
set -e

# Update system packages
echo "Updating system packages..."
sudo apt-get update

# Install ca-certificates and curl for adding Docker's GPG key
echo "Installing ca-certificates and curl..."
sudo apt-get install -y ca-certificates curl

# Prepare Docker's GPG key directory
echo "Preparing Docker's GPG key directory..."
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/debian/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add Docker's repository
echo "Adding Docker's repository..."
echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/debian $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

# Update apt packages list
echo "Updating apt packages list..."
sudo apt-get update

# Install Docker Engine, CLI, and plugins
echo "Installing Docker Engine, CLI, and plugins..."
sudo apt-get install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

# Add current user to the Docker group
echo "Adding current user to the Docker group..."
sudo usermod -aG docker $USER
echo "NOTE: You will need to log out and back in for this change to take effect."

# Install prerequisites for GNS3
echo "Installing prerequisites for GNS3..."
sudo apt update && sudo apt install -y python3-pip python3-dev git qemu-kvm qemu-utils libvirt-daemon-system libvirt-clients bridge-utils virt-manager uidmap xterm cmake libelf-dev libpcap-dev virtualenv

# Clone, build, and install Dynamips
echo "Cloning, building, and installing Dynamips..."
git clone https://github.com/GNS3/dynamips.git
cd dynamips
mkdir build && cd build
cmake ..
make
sudo make install
cd ../..
rm -rf dynamips/

# Clone, build, and install uBridge
echo "Cloning, building, and installing uBridge..."
git clone https://github.com/GNS3/ubridge.git
cd ubridge
make
sudo make install
cd ..
rm -rf ubridge/

# Set up virtualenv for GNS3
echo "Setting up virtualenv for GNS3..."
mkdir BADASS
cd BADASS
virtualenv venv
source venv/bin/activate

# Install GNS3 GUI, GNS3 Server, and PyQt5
echo "Installing GNS3 GUI, GNS3 Server, and PyQt5..."
pip3 install gns3-gui gns3-server pyqt5==5.14.0

# Completion message
echo "Setup complete. Please log out and log back in for Docker group changes to take effect. Then, verify Docker installation by running 'docker run hello-world'."
echo "GNS3 installation is complete. Remember to activate the virtual environment ('source venv/bin/activate') before using GNS3."
