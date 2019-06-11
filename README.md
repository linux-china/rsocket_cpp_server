RSocket LevelDB Server
================
LevelDB is a fast key-value storage library written at Google that provides an ordered mapping from string keys to string values.
RSocket LevelDB server supplies RSocket interface to remote client. 

### Why LevelDB with RSocket

* Remote access from other applications
* Easy to develop SDK for other languages: Java, Python, Node.js, C++ etc
* Cli? already support by rsocket-cli

### How to setup development env

Please use sail and take a look at .sail/Dockerfile 

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