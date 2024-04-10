#!/bin/bash

set -e

if [ -z "$1" ]; then
  echo "Usage: $0 <version>"
  exit 1
fi

VERSION=$1

if [ "$VERSION" != "1" ] && [ "$VERSION" != "2" ]; then
  echo "Invalid version. Version must be either 1 or 2."
  exit 1
fi

echo "Enter Docker Hub password: "
read -s DOCKER_PASSWORD
echo "$DOCKER_PASSWORD" | docker login -u lorenzoedoardofrancesco --password-stdin

docker build -t lorenzoedoardofrancesco/catsanddogs_lsimanic:v$VERSION .
docker push lorenzoedoardofrancesco/catsanddogs_lsimanic:v$VERSION
