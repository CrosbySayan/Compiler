FROM ubuntu:22.04

# Install build essentials (e.g., gcc, make, etc.)
RUN apt-get update && \
    apt-get install -y build-essential && \
    apt-get clean

# Set the working directory inside the container
WORKDIR /workspace
