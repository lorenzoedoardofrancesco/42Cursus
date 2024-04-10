#!/bin/bash

apk add sshpass

SERVER_IP=192.168.56.110
K3S_URL=https://$SERVER_IP:6443

while ! nc -z $SERVER_IP 6443; do sleep 1; done

TOKEN=$(sshpass -p vagrant ssh -o StrictHostKeyChecking=no vagrant@$SERVER_IP sudo cat /var/lib/rancher/k3s/server/node-token)

curl -sfL https://get.k3s.io | K3S_URL=$K3S_URL K3S_TOKEN=$TOKEN INSTALL_K3S_EXEC="--flannel-iface eth1" sh -

echo "alias k='kubectl'" >> /etc/profile.d/kubectl.sh

