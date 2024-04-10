#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <IP Address>"
    exit 1
fi

IP_ADDRESS="$1"

HOSTS_FILE="/etc/hosts"

DOMAINS=(
    "lsimanic.42.fr"
    "portfolio.lsimanic.42.fr"
    "portainer.lsimanic.42.fr"
    "phpmyadmin.lsimanic.42.fr"
    "prometheus.lsimanic.42.fr"
)

for DOMAIN in "${DOMAINS[@]}"; do
    sed -i "/$DOMAIN/d" "$HOSTS_FILE"
done

for DOMAIN in "${DOMAINS[@]}"; do
    echo "$IP_ADDRESS $DOMAIN" >> "$HOSTS_FILE"
done
