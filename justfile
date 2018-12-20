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
setup:
  brew install glog
  brew install gflags
  brew install folly
  brew install leveldb
  brew install yschimke/tap/rsocket-cli

# test after server started
cli_test:
  rsocket-cli --request -m "get" -i "nick" tcp://localhost:42252