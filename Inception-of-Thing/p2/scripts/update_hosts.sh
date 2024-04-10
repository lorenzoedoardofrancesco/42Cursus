IP="192.168.56.110"
HOST1="app1.com"
HOST2="app2.com"

update_hosts() {
    local ip="$1"
    local host="$2"
    if ! grep -q "$ip $host" /etc/hosts; then
        echo "Adding $host to your /etc/hosts"
        echo -e "$ip $host" | sudo tee -a /etc/hosts >/dev/null
    else
        echo "$host already exists in /etc/hosts"
    fi
}

update_hosts $IP $HOST1
update_hosts $IP $HOST2
