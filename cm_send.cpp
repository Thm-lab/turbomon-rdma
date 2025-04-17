#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <openssl/sha.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <thread>
#include <vector>
#include "nlohmann/json.hpp"

#include "data_load/data_load.h"
#include "operations/matrix.h"
#include "rdma/rdma-utils.h"

#define BUFFER_SIZE 125000000

int main(int argc, char* argv[]) {
    // 获取服务器 addr
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <server_ip>" << std::endl;
        return -1;
    }
    const char* server_ip = argv[1];

    char *start_buf, *rdma_buf;
    start_buf = (char*)malloc(BUFFER_SIZE);
    rdma_buf = (char*)malloc(1000);

    std::ifstream cm_json(cm_json_path);
    Matrix data = load_cm_from_json(cm_json);

    // 二维数组按行扁平到start_buf中
    // 8行 312500列
    uint32_t offset = 0;
    for (int i = 0; i < data.size(); i++) {
        uint32_t cols = data[i].size();
        std::memcpy(start_buf + offset * sizeof(int), data[i].data(),
                    cols * sizeof(int));
        offset += cols;
    }

    std::cout << "data load complete, data size = " << offset << std::endl;

    // 把一维数组通过rdma发过去
    auto* server = new rdma_server(server_ip, 1245, start_buf,
                                   offset * sizeof(int), rdma_buf, 1000);
    server->start();

    while (1) {
    }

    return 0;
}
