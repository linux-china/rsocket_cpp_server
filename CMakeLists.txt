cmake_minimum_required(VERSION 3.12)
project(rsocket_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

if (APPLE)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,integer -fno-sanitize=unsigned-integer-overflow -fsanitize=address")
    SET(ADDITIONAL_LIBRARIES ReactiveSocket yarpl folly glog gflags leveldb)
else ()
    set(ADDITIONAL_LIBRARIES ReactiveSocket leveldb snappy yarpl folly glog gflags unwind pthread dl double-conversion boost_regex boost_filesystem boost_program_options boost_context boost_chrono boost_date_time boost_thread boost_system boost_atomic event iberty)
endif ()

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
add_executable(leveldb_server main.cpp)
target_link_libraries(leveldb_server
        ${ADDITIONAL_LIBRARIES} ${OPENSSL_LIBRARIES}
        )

# rsocket request/response client
add_executable(leveldb_client leveldb_client.cpp)
target_link_libraries(leveldb_client
        ${ADDITIONAL_LIBRARIES} ${OPENSSL_LIBRARIES}
        )
