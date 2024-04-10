#!/bin/bash

curl -sfL https://get.k3s.io | INSTALL_K3S_EXEC="--flannel-iface eth1" K3S_KUBECONFIG_MODE="644" sh -
echo "alias k='kubectl'" >> /etc/profile.d/kubectl.sh
