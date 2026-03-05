# Cloud-1

## Introduction

The *cloud-1* project challenges you to deploy a resilient web infrastructure on a public cloud provider. You can find the project description in the [PDF available in this repository](https://github.com/lorenzoedoardofrancesco/42Cursus/raw/main/cloud-1/cloud-1.pdf).

The entire stack is provisioned and managed through **Ansible** playbooks on **AWS**, from EC2 instance creation to service deployment. The architecture is fully containerized via **Docker Compose** and includes:

- **WordPress** with **MariaDB** and **Redis** caching
- **Nginx** reverse proxy with TLS
- **phpMyAdmin** for database management
- **Portainer** for container monitoring
- A static **portfolio** site

Credentials are secured with **Ansible Vault**, and `Makefile` targets provide shortcuts for deploying, restarting, stopping, and resetting the entire stack.

## Setting Up Ansible

To install Ansible along with the necessary AWS SDKs, follow the below script. This script creates a Python virtual environment, installs Ansible, and the required Amazon Web Services SDKs (Boto and Boto3) for Ansible to interact with AWS services.

```bash
#!/bin/bash

# Create a Python virtual environment
python3 -m venv ../venv

# Activate the virtual environment
source ../venv/bin/activate

# Upgrade pip, setuptools, and wheel
pip install --upgrade pip setuptools wheel

# Install Ansible, Boto, and Boto3
pip install ansible boto boto3

# Install necessary Ansible collections for AWS
ansible-galaxy collection install amazon.aws

echo -e "\nTo activate the virtual environment, run the following command:"
echo "source ./venv/bin/activate"
```