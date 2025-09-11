#!/bin/bash

IMAGE_NAME="ubuntu-builder"

docker buildx build --platform linux/amd64 -t $IMAGE_NAME .

if [ $? -ne 0 ]; then
  echo "Docker build failed. Exiting."
  exit 1
fi

# Runs the container with current directory mounted
echo "Running Docker container..."
docker run --rm -it --platform linux/amd64 \
    -v "$PWD":/workspace \
    -w /workspace \
    $IMAGE_NAME bash