cmake_minimum_required(VERSION 3.16)
project(countmin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# 生成compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenSSL REQUIRED)
pkg_search_module(RDMA REQUIRED librdmacm)
pkg_search_module(IBVERBS REQUIRED libibverbs)

include_directories(include)
include_directories(${IBVERBS_INCLUDE_DIRS})
include_directories(${RDMA_INCLUDE_DIRS})

link_directories(${IBVERBS_LIBRARY_DIRS})
link_directories(${RDMA_LIBRARY_DIRS})

add_library(rdmacm_tools STATIC src/rdma/common.c)
set(rdma_libs
        pthread
        ibverbs
        rdmacm
        rdmacm_tools
)

set(cm_send_src
        cm_send.cpp
        src/rdma/rdma_server.cpp
        src/operations/matrix.cpp
        src/data_load/data_load.cpp
)
set(cm_recv_src
        cm_recv.cpp
        src/rdma/rdma_client.cpp
        src/hash/hash.cpp
        src/hash/MurmurHash3.cpp
        src/operations/matrix.cpp
        src/data_load/data_load.cpp
        src/operations/operations.cpp
)

set(cs_send_src
        cs_send.cpp
        src/rdma/rdma_server.cpp
        src/operations/matrix.cpp
        src/data_load/data_load.cpp
)
set(cs_recv_src
        cs_recv.cpp
        src/rdma/rdma_client.cpp
        src/hash/hash.cpp
        src/hash/MurmurHash3.cpp
        src/operations/matrix.cpp
        src/data_load/data_load.cpp
        src/operations/operations.cpp
)

set(es_send_src
        es_send.cpp
        src/rdma/rdma_server.cpp
        src/operations/matrix.cpp
        src/data_load/data_load.cpp
)
set(es_recv_src
        es_recv.cpp
        src/rdma/rdma_client.cpp
        src/hash/hash.cpp
        src/hash/MurmurHash3.cpp
        src/operations/matrix.cpp
        src/data_load/data_load.cpp
        src/operations/operations.cpp
)

set(hp_send_src
        hp_send.cpp
        src/rdma/rdma_server.cpp
        src/operations/matrix.cpp
        src/data_load/data_load.cpp
)
set(hp_recv_src
        hp_recv.cpp
        src/rdma/rdma_client.cpp
        src/hash/hash.cpp
        src/hash/MurmurHash3.cpp
        src/operations/matrix.cpp
        src/data_load/data_load.cpp
        src/operations/operations.cpp
)

set(um_send_src
        um_send.cpp
        src/rdma/rdma_server.cpp
        src/operations/matrix.cpp
        src/data_load/data_load.cpp
)
set(um_recv_src
        um_recv.cpp
        src/rdma/rdma_client.cpp
        src/hash/hash.cpp
        src/hash/MurmurHash3.cpp
        src/operations/matrix.cpp
        src/data_load/data_load.cpp
        src/operations/operations.cpp
)

set(sl_send_src
        sl_send.cpp
        src/rdma/rdma_server.cpp
        src/operations/matrix.cpp
        src/data_load/data_load.cpp
)
set(sl_recv_src
        sl_recv.cpp
        src/rdma/rdma_client.cpp
        src/hash/hash.cpp
        src/hash/MurmurHash3.cpp
        src/operations/matrix.cpp
        src/data_load/data_load.cpp
        src/operations/operations.cpp
)

# 可执行文件存放目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 编译链接
add_executable(cm_send ${cm_send_src})
target_link_libraries(cm_send ${rdma_libs})
add_executable(cs_send ${cs_send_src})
target_link_libraries(cs_send ${rdma_libs})
add_executable(es_send ${es_send_src})
target_link_libraries(es_send ${rdma_libs})
add_executable(hp_send ${hp_send_src})
target_link_libraries(hp_send ${rdma_libs})
add_executable(um_send ${um_send_src})
target_link_libraries(um_send ${rdma_libs})
add_executable(sl_send ${sl_send_src})
target_link_libraries(sl_send ${rdma_libs})


add_executable(cm_recv ${cm_recv_src})
target_link_libraries(cm_recv ${rdma_libs})
add_executable(cs_recv ${cs_recv_src})
target_link_libraries(cs_recv ${rdma_libs})
add_executable(es_recv ${es_recv_src})
target_link_libraries(es_recv ${rdma_libs})
add_executable(hp_recv ${hp_recv_src})
target_link_libraries(hp_recv ${rdma_libs})
add_executable(um_recv ${um_recv_src})
target_link_libraries(um_recv ${rdma_libs})
add_executable(sl_recv ${sl_recv_src})
target_link_libraries(sl_recv ${rdma_libs})