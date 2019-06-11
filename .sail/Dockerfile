FROM codercom/ubuntu-dev-gcc8

RUN sudo apt-get update -y && \
    sudo apt-get install -y wget bash-completion cmake

# Folly & RSocket-cpp build
RUN sudo apt-get install -y \
        g++ \
        automake \
        autoconf \
        autoconf-archive \
        libtool \
        libboost-all-dev \
        libevent-dev \
        libdouble-conversion-dev \
        libgoogle-glog-dev \
        libgflags-dev \
        liblz4-dev \
        liblzma-dev \
        libsnappy-dev \
        make \
        zlib1g-dev \
        binutils-dev \
        libjemalloc-dev \
        libssl-dev \
        libunwind8-dev \
        libelf-dev \
        libdwarf-dev \
        libiberty-dev

# just command runner install
RUN curl -LSfs https://japaric.github.io/trust/install.sh | sudo sh -s -- --git casey/just --target x86_64-unknown-linux-musl --to /usr/local/bin
RUN echo "complete -W '$(just --summary)' just" >> ~/.bashrc

# install VS Code extensions
RUN code-server --extensions-dir ~/.vscode/extensions --install-extension ms-vscode.cpptools
