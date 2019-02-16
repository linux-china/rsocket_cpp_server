RSocket LevelDB Server
================
LevelDB is a fast key-value storage library written at Google that provides an ordered mapping from string keys to string values.
RSocket LevelDB server supplies RSocket interface to remote client. 

### Why LevelDB with RSocket

* Remote access from other applications
* Easy to develop SDK for other languages: Java, Python, Node.js, C++ etc
* Cli? already support by rsocket-cli

### Mac Setup

* Refer setup recipe in justfile
* Install rsocket-cpp from https://github.com/rsocket/rsocket-cpp  If any problem, please rename /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/math.h 

### Ubuntu Setup

You need to build Folly, rsocket-cpp and leveldb from source code.  Please refer setup_ubuntu in justfile.

* Please use Release mode: cmake -DCMAKE_BUILD_TYPE=Release ..
* rsocket-cpp: please turn off all tests build & remove tck build
* setups as following:
```
mkdir _build
cd _build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
```

### CentOS Setup
Please refer setup_centos in justfile to setup env, and use last gcc version. 
Build setups just like Ubuntu. 

### RSocket protocol for LevelDB

* metadata's format is like levelDB's method + " " + key, such as "get nick", "delete nick"
* data is value.  Get & delete method, value is empty string.

### Todo

* Sharding? sharding by key in different buckets
* Shutdown gracefully? Use fireAndForget() to trigger shutdown event, metadata is 'halt' and data is token 
* RocksDB? almost same. https://github.com/facebook/rocksdb 

# References

* leveldb: https://github.com/google/leveldb
* The gflags package contains a C++ library that implements commandline flags processing: https://github.com/gflags/gflags
* Folly: Facebook Open-source Library https://github.com/facebook/folly
* yarpl: Yet Another Reactive Programming Library https://github.com/rsocket/rsocket-cpp/tree/master/yarpl
* Google logging: https://github.com/google/glog