#!/bin/bash

echo "BADASS - Part 3: Discovering BGP with EVPN."
echo "Import the P3 Project into GNS3 and start all router nodes."

read -p "Press enter when ready:" 

# Directory where the script and conf files are located
SCRIPT_DIR="$(dirname "$0")"

# Get a list of all running containers (just the container IDs)
container_ids=$(docker ps -q)

for id in $container_ids; do
  # For each container, get its hostname
  hostname=$(docker inspect --format '{{ .Config.Hostname }}' "$id")
  
  # Construct the conf file name based on the hostname
  conf_file="$SCRIPT_DIR/${hostname}"
  
  # Check if the configuration file exists
  if [ -f "$conf_file" ]; then
    echo "Found configuration for $hostname, executing commands..."
    
    # Read each line in the conf file and execute it inside the container
    docker cp $conf_file $id:/
    docker exec $id bash /$conf_file
  else
    echo "No configuration found for $hostname."
  fi
done

