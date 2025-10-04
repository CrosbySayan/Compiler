FROM ubuntu:22.04

# Install build essentials (e.g., gcc, make, etc.)
RUN apt-get update && \
    apt-get install -y build-essential && \
    apt-get clean

# Removes ugly root: /workspace for nicer colors
RUN echo 'export PS1="\[\e[1;36m\]docker\[\e[0m\]:\[\e[1;33m\]\W\[\e[0m\] ❯ "' >> /root/.bashrc

RUN echo 'export PS1="\[\e[1;32m\]\u@\h\[\e[0m\]:\[\e[1;34m\]\w\[\e[0m\]\$ "' >> /etc/bash.bashrc && \
    echo 'alias ls="ls --color=auto"' >> /etc/bash.bashrc && \
    echo 'alias grep="grep --color=auto"' >> /etc/bash.bashrc
# Set the working directory inside the container
WORKDIR /workspace
