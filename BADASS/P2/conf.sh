#!/bin/bash

echo "BADASS - Part 2: Discovering a VXLAN."
echo ""
echo "Import the P2 Project into GNS3 and start all nodes. Then select an option:"
echo "1. Static VXLAN configuration"
echo "2. Dynamic Multicast VXLAN configuration"

option=0
while [[ "$option" -ne 1 && "$option" -ne 2 ]]; do
  read -p "Option (1/2): " option
  if [[ "$option" -ne 1 && "$option" -ne 2 ]]; then
    echo "Invalid option. Please select 1 or 2."
  fi
done

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
    while IFS= read -r line; do
      if [ "$option" -eq 2 ]; then 
         line=$(echo "$line" | sed -E 's/remote 10\.1\.1\.(1|2) local 10\.1\.1\.(2|1)/group 239.1.1.1/g')
      fi
      docker exec "$id" $line
    done < "$conf_file"
  else
    echo "No configuration found for $hostname."
  fi
done

