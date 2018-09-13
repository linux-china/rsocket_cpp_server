cmake_minimum_required(VERSION 3.12)
project(rsocket_server)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fsanitize=address,integer -fno-sanitize=unsigned-integer-overflow -fsanitize=address")

add_executable(rsocket_server main.cpp)
#target_link_libraries(rsocket_server folly )
target_link_libraries(rsocket_server
        ReactiveSocket
        yarpl
        folly
        glog
        gflags
        )
