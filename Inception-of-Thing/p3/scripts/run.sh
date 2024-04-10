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
