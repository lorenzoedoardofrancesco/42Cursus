# Inception-of-Things Project Documentation

## Introduction

The **Inception-of-Things** project is designed to deepen your understanding by engaging you in the practical application of **K3d** and **K3s** with **Vagrant**. Throughout this project, you will learn how to configure a personal virtual machine using Vagrant with your preferred distribution. The project guides you through utilizing **K3s** and its Ingress capabilities, and introduces **K3d**, a tool that simplifies Kubernetes operations. These foundational steps will embark you on your journey with Kubernetes, offering a minimal yet essential introduction to the complexities of this orchestration tool.

## Table of Contents

This project is structured into three main parts, which should be completed in the following order:

1. **[K3s and Vagrant](#k3s-and-vagrant)**  
   - [Preparation of the Working Environment](#preparation-of-the-working-environment)
   - [Setup two machines using Vagrant](#setup-two-machines-using-vagrant)
   - [Install and configure K3s in controller and agent modes](#install-and-configure-k3s-in-controller-and-agent-modes)


2. **[K3s and Three Simple Applications](#k3s-and-three-simple-applications)**
   - [VM Configuration with Vagrant](#vm-configuration-with-vagrant)
   - [Kubernetes Deployments and Services](#kubernetes-deployments-and-services)
   - [Ingress Configuration](#ingress-configuration)

3. **[K3s and Vagrant](#k3s-and-vagrant)**  
   - [Setup Script for K3d and Argo CD](#setup-script-for-k3d-and-argo-cd)
   - [Continuous Integration Setup](#continuous-integration-setup)
   - [Continuous Deployment via GitHub and DockerHub](#continuous-deployment-via-github-and-dockerhub)

## K3s and Vagrant

### Preparation of the Working Environment

Before diving into the core project, it's crucial to set up your working environment. This involves installing **VirtualBox** and **Vagrant**, foundational tools for creating and managing virtual machines which will host our Kubernetes clusters.

#### Installing VirtualBox

**VirtualBox** is a powerful *x86 and AMD64/Intel64* virtualization product for enterprise as well as home use.

1. Download the Latest Version of `VirtualBox`:

   ```bash
   wget https://download.virtualbox.org/virtualbox/7.0.14/virtualbox-7.0_7.0.14-161095~Debian~bookworm_amd64.deb
   ```

2. After downloading, install VirtualBox using the Debian package manager:

   ```bash
   sudo apt install -y ./virtualbox-*.deb
   rm -rf ./virtualbox-*.deb
   ```

3. Check the installed VirtualBox version to ensure it was installed correctly:

   ```bash
   virtualbox --help
   ```

#### Installing Vagrant

**Vagrant** is an open-source tool designed for building and managing virtual machine environments in a simple workflow.

1. Download the Latest Version of `Vagrant`:

   ```bash
   wget https://releases.hashicorp.com/vagrant/2.4.1/vagrant_2.4.1-1_amd64.deb
   ```

2. After downloading, install Vagrant by running:

   ```bash
   sudo apt install -y ./vagrant_*.deb
   rm -rf ./vagrant_*.deb
   ```

3. Check the installed Vagrant version to ensure it was installed correctly:
   ```bash
   vagrant --version
   ```

### Setup two machines using Vagrant

The core of the first part is a Vagrantfile designed to automate the setup of two virtual machines for our Kubernetes cluster:

```ruby
# -*- mode: ruby -*-
# vi: set ft=ruby :

CPU = 1
MEMORY = 1024
IP_SERVER = "192.168.56.110"
IP_WORKER = "192.168.56.111"
ALPINE_VERSION = "319"
BOX_VERSION = "4.3.12"

Vagrant.configure("2") do |config|
    config.vm.provider "virtualbox" do |vb|
        vb.customize ["modifyvm", :id, "--cpus", CPU]
        vb.customize ["modifyvm", :id, "--memory", MEMORY]
        vb.linked_clone = true
    end

    {"#{ENV['USER']}S" => IP_SERVER, "#{ENV['USER']}SW" => IP_WORKER}.each do |hostname, ip|
    config.vm.define hostname do |vm_config|
      vm_config.vm.box = "generic/alpine#{ALPINE_VERSION}"
      vm_config.vm.box_version = BOX_VERSION
      vm_config.vm.hostname = hostname
      vm_config.vm.network "private_network", ip: ip
      vm_config.vm.provider "virtualbox" do |vb|
        vb.name = hostname
      end
      script_path = hostname.include?("SW") ? "./scripts/worker.sh" : "./scripts/server.sh"
      vm_config.vm.provision "shell", path: script_path
    end
  end
end
```

We have used *Vagrant* and *VirtualBox* to orchestrate the creation of two virtual machines, both running *Alpine Linux 3.19*, to establish a lightweight Kubernetes environment using **K3s**. Through a Ruby loop, we dynamically configured one machine as a server and the other as a worker, each allocated with *1 CPU* and *1024 MB of RAM* to ensure a balance between efficiency and performance.

The server was assigned an IP of `192.168.56.110`, and the worker, `192.168.56.111`, establishing a private network for seamless communication between them. The setup process was further streamlined by provisioning scripts:

### Install and configure K3s in controller and agent modes
#### Server Setup Script (`server.sh`)

```bash
#!/bin/bash

curl -sfL https://get.k3s.io | INSTALL_K3S_EXEC="--flannel-iface eth1" K3S_KUBECONFIG_MODE="644" sh -
echo "alias k='kubectl'" >> /etc/profile.d/kubectl.sh
```
This script installs `K3s` in **controller mode** on the server, setting up the Kubernetes control plane. It also creates an alias for `kubectl`, simplifying command-line interactions with Kubernetes.

#### Worker Setup Script (`worker.sh`)
```bash
#!/bin/bash

apk add sshpass

SERVER_IP=192.168.56.110
K3S_URL=https://$SERVER_IP:6443

while ! nc -z $SERVER_IP 6443; do sleep 1; done

TOKEN=$(sshpass -p vagrant ssh -o StrictHostKeyChecking=no vagrant@$SERVER_IP sudo cat /var/lib/rancher/k3s/server/node-token)

curl -sfL https://get.k3s.io | K3S_URL=$K3S_URL K3S_TOKEN=$TOKEN INSTALL_K3S_EXEC="--flannel-iface eth1" sh -

echo "alias k='kubectl'" >> /etc/profile.d/kubectl.sh
```
This script prepares the worker for joining the cluster by installing *K3s* in **agent mode**. It ensures the worker can securely communicate with the server to function as part of the Kubernetes cluster.


## K3s and Three Simple Applications

This section of the project leverages a single virtual machine to host three distinct web applications, all orchestrated by **K3s** in *server mode*. The objective is to configure access to these applications based on the hostname used in the request. Here's how we achieve this setup:

### VM Configuration with Vagrant

```ruby
# -*- mode: ruby -*-
# vi: set ft=ruby :

CPU = 4
MEMORY = 4096
IP_SERVER = "192.168.56.110"
ALPINE_VERSION = "319"
BOX_VERSION = "4.3.12"

Vagrant.configure("2") do |config|
    config.vm.define "#{ENV['USER']}S" do |server|
        server.vm.box = "generic/alpine#{ALPINE_VERSION}"
        server.vm.box_version = BOX_VERSION
        server.vm.hostname = "#{ENV['USER']}S"
        server.vm.network "private_network", ip: IP_SERVER
        server.vm.provider "virtualbox" do |vb|
            vb.name = "#{ENV['USER']}S"
            vb.customize ["modifyvm", :id, "--cpus", CPU]
            vb.customize ["modifyvm", :id, "--memory", MEMORY]
            vb.linked_clone = true
        end
        server.ssh.insert_key = true
        server.vm.synced_folder "./confs", "/vagrant/confs"
        server.vm.provision "shell", path: "./scripts/server.sh"
    end
end
```

This configuration ensures the VM is provisioned with the necessary resources and network settings to host our applications and allows for seamless deployment and management of Kubernetes resources.

### Kubernetes Deployments and Services

Three deployments are configured, each corresponding to a web application. These deployments ensure that each application is replicated as specified, maintaining availability and load distribution. The applications are simple web servers that respond with a unique message identifying each application.

 Each application (*app-one*, *app-two*, and *app-three*) is deployed with its respective number of replicas and unique identifiers. These deployments use the `hello-kubernetes` image, designed to respond with a customizable greeting message, showcasing flexibility in Kubernetes deployments.
  
 **Kubernetes services** are set up for each application, providing *stable* IP addresses and managing load balancing across pods. This is crucial for ensuring that inbound requests are efficiently distributed among available replicas.

### Ingress Configuration

An **Ingress** resource is created to manage access to the applications based on the hostname specified in the request. This configuration enables the server to route traffic to `app1.com` to *app-one*, `app2.com` to *app-two*, and all other requests to *app-three* by default.

  > **Hostname-Based Routing** demonstrates how *Kubernetes Ingress* can use hostnames to route traffic to different services within the cluster, simulating a real-world scenario where *multiple* domains are served by a *single* IP address.

## K3s and Vagrant
In this final part, we explore a setup leveraging **K3d**, a tool that runs *K3s* in Docker containers, facilitating Kubernetes cluster management. This setup aims to demonstrate a continuous integration pipeline using Argo CD, a declarative GitOps continuous delivery tool for Kubernetes.

### Setup Script for K3d and Argo CD
To streamline the installation of `Docker`, `K3d`, `Argo CD`, and other necessary tools, we wrote a Bash script `setup.sh`. This script performs the following actions:

  - Installs Docker Engine, CLI, and plugins, which are prerequisites for running K3d.
  - Adds the current user to the Docker group to run Docker commands without sudo.
  - Installs Kubectl, K3d, and Argo CD CLI tools necessary for managing Kubernetes resources and continuous deployment workflows.

#### `setup.sh`
```bash
#!/bin/bash

echo "Starting setup..."

# Exit script on error
set -e

# Update system packages
echo "Updating system packages..."
sudo apt-get update

# Install ca-certificates and curl for adding Docker's GPG key
echo "Installing ca-certificates and curl..."
sudo apt-get install -y ca-certificates curl

# Prepare Docker's GPG key directory
echo "Preparing Docker's GPG key directory..."
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/debian/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add Docker's repository
echo "Adding Docker's repository..."
echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/debian $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | sudo tee /etc/apt/sources.list.d/docker.list >/dev/null

# Update apt packages list
echo "Updating apt packages list..."
sudo apt-get update

# Install Docker Engine, CLI, and plugins
echo "Installing Docker Engine, CLI, and plugins..."
sudo apt-get install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

# Add current user to the Docker group
echo "Adding current user to the Docker group..."
sudo usermod -aG docker $USER
echo "NOTE: You will need to log out and back in for this change to take effect."

# Install Kubectl
curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl"
chmod +x ./kubectl
sudo mv ./kubectl /usr/local/bin/kubectl
kubectl version --client

# Install for K3D
curl -s https://raw.githubusercontent.com/rancher/k3d/main/install.sh | bash

# Install for ArgoCD-cli
curl -sSL -o argocd https://github.com/argoproj/argo-cd/releases/latest/download/argocd-linux-amd64
chmod +x argocd
sudo mv argocd /usr/local/bin/
```

### Continuous Integration Setup
A secondary script sets up the environment for continuous integration:

  - Creates a K3d cluster with a specific port mapping to access applications deployed within the cluster.
  - Initializes two namespaces: `dev` for the application and `argocd` for the Argo CD components.
  - Installs Argo CD into the argocd namespace and sets up port forwarding to access the Argo CD UI.
  - Configures Argo CD, creates a project, and sets up the application for automatic deployment from our GitHub repository.

#### `run.sh`

```bash
#!/bin/bash

k3d cluster create cluster -p "8888:30001@agent:0" --agents 1
kubectl cluster-info
kubectl create namespace dev
kubectl create namespace argocd
kubectl apply -n argocd -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml

sleep 5

kubectl wait --for=condition=ready pod -l app.kubernetes.io/name=argocd-server -n argocd --timeout=300s

kubectl port-forward svc/argocd-server -n argocd 5000:443 &>/dev/null &
PASSWORD=$(kubectl get secret argocd-initial-admin-secret -n argocd -o jsonpath="{.data.password}" | base64 -d)
argocd login localhost:5000 --username admin --password $PASSWORD --insecure

sleep 20

argocd proj create catsanddogs --upsert
argocd proj add-destination catsanddogs https://kubernetes.default.svc dev
argocd proj add-source catsanddogs https://github.com/lorenzoedoardofrancesco/CatsAndDogs_lsimanic.git
argocd app create catsanddogs \
	--project catsanddogs \
	--repo https://github.com/lorenzoedoardofrancesco/CatsAndDogs_lsimanic.git \
	--path . \
	--dest-server https://kubernetes.default.svc \
	--dest-namespace dev \
	--sync-policy automated

echo "You can now login to argocd on localhost:5000"
echo "Username: admin"
echo "Password: $PASSWORD"
```

### Continuous Deployment via GitHub and DockerHub
In this setup, a GitHub repository and DockerHub work together to facilitate seamless application updates through Argo CD. The process unfolds as follows:

  - Version Update Trigger: A script in the GitHub repository, `to-v2.sh`, modifies `deployment.yaml` to change the application version from `catsanddogs_lsimanic:v1` to `catsanddogs_lsimanic:v2`. This alteration signals an update is required.

  - Argo CD Synchronization: Argo CD, watching the GitHub repository, detects the change and automatically syncs the new configuration, instructing Kubernetes to pull the updated version `v2` from `DockerHub`.

  - Deployment: Kubernetes updates the application pods to the new version, ensuring the deployment reflects the most recent changes specified in the `GitHub` repository.

> This approach demonstrates a GitOps workflow, where a simple change in a GitHub repository (like updating a version tag) triggers an automated deployment process, showcasing the efficiency of integrating source control with Kubernetes deployments.