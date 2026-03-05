# ft_ping

## Introduction

The *ft_ping* project is a from-scratch re-implementation of the `ping` command (reference: **inetutils-2.0**), written in **C** using raw ICMP sockets. The goal is to understand how ICMP echo requests and replies work at the network level, handle signal-driven timing, and produce output identical to the original tool. You can find the project description in the [PDF available in this repository](https://github.com/lorenzoedoardofrancesco/42Cursus/raw/main/ft_ping/ft_ping.pdf).

## Features

### Mandatory

- Sends ICMP `ECHO_REQUEST` packets and listens for `ECHO_REPLY` responses
- Supports IPv4 addresses and hostnames (FQDN without reverse DNS in packet return)
- Verbose mode (`-v`) displaying full IP/ICMP header dumps on errors
- RTT measurement with min/avg/max/stddev statistics
- Output format identical to inetutils-2.0

### Bonus Flags

The implementation goes well beyond the mandatory requirements with the following options:

| Flag | Long | Description |
|------|------|-------------|
| `-c` | `--count` | Stop after sending N packets |
| `-d` | `--debug` | Set the `SO_DEBUG` socket option |
| `-f` | `--flood` | Flood ping (root only) |
| `-i` | `--interval` | Wait N seconds between packets |
| `-l` | `--preload` | Send N packets as fast as possible before normal mode |
| `-n` | `--numeric` | Do not resolve host addresses |
| `-p` | `--pattern` | Fill ICMP packet with a hex pattern |
| `-q` | `--quiet` | Quiet output, only show statistics |
| `-r` | `--ignore-routing` | Bypass routing table (`SO_DONTROUTE`) |
| `-s` | `--size` | Set the number of data bytes to send |
| `-T` | `--tos` | Set Type of Service |
| `-v` | `--verbose` | Verbose output with header dumps |
| `-w` | `--timeout` | Stop after N seconds total |
| `-W` | `--linger` | Seconds to wait for a response |
| | `--ttl` | Set the IP Time To Live |

## Usage

```bash
make
sudo ./ft_ping google.com
sudo ./ft_ping -c 5 -i 2 -s 128 192.168.1.1
sudo ./ft_ping -f -c 1000 localhost
```

## Technical Summary

- **Language:** C (libc only, no external libraries)
- **Raw ICMP sockets** with manual checksum computation
- **POSIX timers** (`timer_create`) for interval scheduling
- **Signal handling** (`SIGINT`, `SIGALRM`) for graceful shutdown and timing
- **Duplicate detection** via bitmap tracking of sequence numbers
- **Custom `sqrt`** implementation (no `libm` dependency beyond linking)
