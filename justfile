# build the project
build:
  { mkdir -p build; cd build; cmake ..; make; }

# run leveldb server
server: build
  ./build/leveldb_server

# run leveldb client
client: build
  ./build/leveldb_client

# setup the environment
setup_mac:
  brew install glog
  brew install gflags
  brew install folly
  brew install leveldb
  brew install yschimke/tap/rsocket-cli

# test after server started
cli_test:
  rsocket-cli --request -m "get nick" -i "" tcp://localhost:42252

setup_ubuntu:
  sudo apt-get install g++ cmake libboost-all-dev libevent-dev libdouble-conversion-dev libgoogle-glog-dev libgflags-dev libiberty-dev libaio-dev libbz2-dev liblz4-dev libzstd-dev liblzma-dev libsnappy-dev make zlib1g-dev binutils-dev libjemalloc-dev libssl-dev pkg-config libunwind8-dev libelf-dev libdwarf-dev libsqlite3-dev google-perftools doxygen libtcmalloc-minimal4
