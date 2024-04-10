#!/bin/bash

python3 -m venv ../venv
source ../venv/bin/activate
pip install --upgrade pip setuptools wheel
pip install ansible boto boto3
ansible-galaxy collection install amazon.aws

echo -e "\nTo activate the virtual environment, run the following command:"
echo "source ./venv/bin/activate"