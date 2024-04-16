# ft_nmap — A High-Speed Multithreaded Port Scanner

**ft_nmap** is a fast, multithreaded network scanner inspired by **nmap**, built from scratch in C using raw packet crafting and direct packet capture.  
It supports classic scan techniques, enriched with advanced threading and filtering logic to maximize performance and minimize scan time.

Unlike nmap, **ft_nmap** emphasizes **speed** and **multithreading**, handling hundreds of concurrent probes with clean, structured output.

## Project Description

### Mandatory Features

- Supports IPv4 addresses and hostnames (FQDN — no DNS resolution)
- Multithreaded execution with configurable thread count (default: 0, max: 250)
- Supported scan types:
  - **SYN**
  - **NULL**
  - **ACK**
  - **FIN**
  - **XMAS**
  - **UDP**
- Supports multiple simultaneous scan types
- Ports input by list or range (default: 1–1024, max 1024 ports)
- Automatic service type resolution (no version detection)
- Human-readable scan reports with execution time
- IP/host list import from file

### Bonus Features

- ICMP ping with latency measurement
- Reverse DNS lookup
- CIDR range support
- Optional randomization control (`--no-randomize`)
- Disable ping option (`--no-ping`)
- Top ports scanning (`--top-ports`)
- Extra scans:
  - **Window Scan** (`-sW`)
  - **Connect Scan** (`-sC`)
- UDP probe rate control (`--udp-rate`)
- Source address spoofing (`--spoof-address`)

## Multithreading & Performance

One of the key design goals of **ft_nmap** is **performance under high concurrency**.  
By crafting packets manually and managing threading with mutexes, **ft_nmap** can fire off hundreds of probes in parallel, making it significantly faster than traditional scanners in most common use cases.

## Usage

```bash
./ft_nmap --ip 192.168.0.42 --ports 20-80 --scan SYN,UDP --speedup 100
```
```bash
./ft_nmap --file targets.txt --top-ports 50 --scan FIN --no-ping --speedup 250
```

## Technical Summary

- **Language:** C (Standard Library + libpcap + pthread)
- **No dependencies on external scanners (nmap not used)**
- **Manual packet crafting with raw sockets**
- **Thread-safe operations with mutex protection**
- **Full pcap filter setup for response capture**

## Project Insights

This project gave us a very practical introduction to network scanning.  
We relied on **libpcap** for packet capture and filtering, built a thread-pool architecture with **pthreads** to launch probes in parallel, and spent most of our effort on timing accuracy, error handling and thread-safe data sharing.
Tuning socket options, synchronizing shared queues and preventing race conditions under heavy concurrency were the main technical challenges we had to overcome.

##  Authors

Made with passion as part of the **École 42 cursus**.  

**Authors:**  
- [Axel Brisse](https://github.com/haksell) 
- [Lorenzo Edoardo Francesco Simanic](https://github.com/lorenzoedoardofrancesco)  
