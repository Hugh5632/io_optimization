cmake_minimum_required(VERSION 3.17)
project(io_optimization)
find_package(glog REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(CFLAGS
        -m64
        -pthread
        -march=native
        #        -include /usr/local/include/dpdk/rte_config.h
        #        -O3
        -ggdb
        ${WERROR_FLAGS})
add_compile_options(${CFLAGS})

set(INC_DIR
        /usr/local/include)

set(LINK_DIR /usr/local/lib)

include_directories(${INC_DIR})
link_directories(${LINK_DIR})


add_executable(io_optimization main.cpp write_optimization.cc write_optimization.h read_optimization.cc read_optimization.h common/common.cc common/common.h)

target_link_libraries(
        io_optimization
        glog::glog
        libgflags.a
        libglog.a

)