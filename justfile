# build the project
build:
  { mkdir -p build; cd build; cmake ..; make; }

# run rsocket stream server
server_stream: build
  ./build/rsocket_stream_server

# run client
client: build
  ./build/rsocket_client

# setup the environment
setup:
  brew install glog
  brew install gflags
  brew install folly
  brew install yschimke/tap/rsocket-cli

# test after server started
test:
  rsocket-cli --stream -i "Jackie" tcp://localhost:9898