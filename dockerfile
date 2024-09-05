FROM --platform=linux/amd64  ubuntu:24.04
# Platform amd64 necessario apenas para r-studio. Todo resto funciona sem isso

#COPY . /

# Update and install necessary packages
RUN apt-get update && apt-get install -y \
    build-essential \
    clang \
    cmake \
    git \
    vim \
    wget \
    zlib1g-dev \
    libncurses-dev \
    libgmp-dev \
    libreadline-dev \
    libssl-dev \
    libedit-dev \
    libunwind-dev \
    lsb-release \
    gnuplot \
    gnuplot-x11

# Set default C compiler to clang
ENV CC=/usr/bin/clang++

# Set working directory
WORKDIR /work

# Expose ports for development
EXPOSE 3000
EXPOSE 4000

# Set default command
CMD ["bash"]
