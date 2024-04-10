#!/bin/bash

source ../venv/bin/activate

for cmd in openssl ansible-vault; do
	if ! command -v $cmd &>/dev/null; then
		echo "Error: $cmd could not be found. Please install $cmd."
		exit 1
	fi
done

mkdir -p ../vault
cd ../vault

if [ ! -f vault.pass ]; then
    openssl rand -base64 2048 > vault.pass
    chmod 600 vault.pass
    echo "Vault password file created."
else
    echo "Vault password file already exists."
fi

if [ -z "$AWS_ACCESS_KEY_ID" ]; then
    read -p "Enter AWS Access Key ID: " AWS_ACCESS_KEY_ID
fi

if [ -z "$AWS_SECRET_ACCESS_KEY" ]; then
    read -s -p "Enter AWS Secret Access Key: " AWS_SECRET_ACCESS_KEY
    echo
fi

credentials_content="ec2_access_key: $AWS_ACCESS_KEY_ID\nec2_secret_key: $AWS_SECRET_ACCESS_KEY"
echo -e "$credentials_content" > temp_credentials.yml

ansible-vault encrypt temp_credentials.yml --vault-password-file vault.pass
mv temp_credentials.yml encrypted_credentials.yml

echo "Vault updated with AWS credentials."