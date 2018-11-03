cmake_minimum_required(VERSION 3.12)
project(rsocket_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,integer -fno-sanitize=unsigned-integer-overflow -fsanitize=address")


# openssl
find_package(PkgConfig REQUIRED)
pkg_search_module(OPENSSL REQUIRED openssl)

if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIRS})
    message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
else ()
    # Error; with REQUIRED, pkg_search_module() will throw an error by it's own
endif ()

# rsocket stream server
add_executable(rsocket_stream_server main.cpp)
target_link_libraries(rsocket_stream_server
        ReactiveSocket yarpl folly glog gflags
        )
# rsocket request/response server
add_executable(rsocket_response_server main_response.cpp)
target_link_libraries(rsocket_response_server
        ReactiveSocket yarpl folly glog gflags
        )

# rsocket request/response client
add_executable(rsocket_request_requester client_request.cpp)
target_link_libraries(rsocket_request_requester
        ReactiveSocket yarpl folly glog gflags
        )
