# Cloud-1

### Goal
Deploy a resilient WordPress architecture with a Public Cloud Provider. This project aims to demonstrate the ability to create a highly available and scalable WordPress environment on AWS, leveraging Ansible for automation and configuration management.

### Cloud Provider
**Amazon Web Services (AWS)** - This project is deployed on AWS, utilizing its robust and scalable infrastructure to ensure the WordPress site is resilient and performs efficiently under varying loads.

### Configuration Management and Automation
**Ansible** is used for automating the deployment and configuration of resources in AWS. It simplifies cloud provisioning, configuration management, application deployment, intra-service orchestration, and many other IT needs.

### Setting Up Ansible

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