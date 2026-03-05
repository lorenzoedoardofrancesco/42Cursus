# ft_traceroute

## Introduction

The *ft_traceroute* project is a from-scratch re-implementation of the `traceroute` command, written in **C** using raw sockets. The program maps the network path between the local machine and a remote host by incrementally increasing the TTL (Time To Live) of outgoing packets and analyzing ICMP `TIME_EXCEEDED` and `DEST_UNREACH` responses from intermediate routers. You can find the project description in the [PDF available in this repository](https://github.com/lorenzoedoardofrancesco/42Cursus/raw/main/ft_traceroute/ft_traceroute.pdf).

## Features

### Mandatory

- Sends UDP probes (default) or ICMP `ECHO_REQUEST` probes with incrementing TTL
- Displays each hop with hostname, IP address, and round-trip time
- Supports IPv4 addresses and hostnames (FQDN without DNS resolution in hop display)
- Output format identical to the system `traceroute`

### Bonus Flags

The implementation extends the mandatory requirements with the following options:

| Flag | Long | Description |
|------|------|-------------|
| `-f` | `--first-hop` | Set initial hop distance (TTL) |
| `-I` | `--icmp` | Use ICMP ECHO as probe instead of UDP |
| `-i` | `--interface` | Bind to a specific network interface |
| `-m` | `--max-hop` | Set maximum hop count (default: 30) |
| `-n` | `--numeric` | Do not resolve IP addresses to hostnames |
| `-p` | `--port` | Set destination port (default: 33434) |
| `-q` | `--queries` | Number of probe packets per hop (default: 3) |
| `-s` | `--source` | Use a specific source address |
| `-t` | `--tos` | Set Type of Service (TOS) |
| `-w` | `--wait` | Seconds to wait for a response (default: 3) |

## Usage

```bash
make
sudo ./ft_traceroute google.com
sudo ./ft_traceroute -I -m 20 -q 1 192.168.1.1
sudo ./ft_traceroute -n -w 5 8.8.8.8
```

## Technical Summary

- **Language:** C (libc only, no external libraries)
- **Dual probe modes:** UDP datagrams or ICMP echo requests
- **Raw ICMP socket** for receiving `TIME_EXCEEDED` and `DEST_UNREACH` responses
- **`select()`-based** timeout handling per probe (no `poll`/`fcntl` allowed)
- **ICMP unreachable code handling** (`!N`, `!H`, `!P`, `!F`, `!S` annotations)
- **Signal handling** (`SIGINT`) for graceful termination
