#include <arpa/inet.h>
#include <cerrno>
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <thread>
#include <tuple>
#include <vector>

#include "config/op_enable.h"
#include "hash/hash.h"
#include "operations/matrix.h"
#include "operations/operations.h"
#include "rdma/rdma-utils.h"

#define BUFFER_SIZE 125000000
#define _WRS_PACK_ALIGN(x) __attribute__((packed, aligned(x)))

int recv_buf[BUFFER_SIZE / 4] = {0};

int main(int argc, char* argv[]) {
    int ret;
    bool flag;

    // 获取服务器 addr
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <server_ip>" << std::endl;
        return -1;
    }
    const char* server_ip = argv[1];

    char *start_buf, *rdma_buf;
    start_buf = (char*)malloc(1000);
    rdma_buf = (char*)malloc(1000);

    strcpy(start_buf, "hello world form client");
    auto* client = new rdma_client(server_ip, 1245, start_buf, 1000, recv_buf,
                                   BUFFER_SIZE);
    client->start();

    uint32_t es_rows = 3, es_cols = 1000;

    uint32_t array_len = 0;

    Matrix es_matrix;

    int test_times = 50;            // 测试次数
    std::vector<double> latencies;  // 存储每次迭代的延迟时间
    uint64_t total_data_size = 0;   // 存储总的数据量

    while (test_times--) {
        auto start = std::chrono::high_resolution_clock::now();  // 记录开始时间

        // 从rdma拿数据
        client->rdma_read();
        char* rdma_array = client->get_rdma_buf();
        array_len = client->get_rdma_size() / sizeof(int);

        // 算子处理
        es_matrix = array_to_matrix(rdma_array, array_len, es_rows);

        uint32_t src_ip = (192 << 24) | (168 << 16) | (8 << 8) | 1;
        uint32_t dst_ip = (192 << 24) | (168 << 16) | (8 << 8) | 2;
#if OP_MAX
        uint32_t max_data = operator_max(es_matrix, src_ip, dst_ip);
#endif  // OP_MAX
#if OP_MIN
        uint32_t min_data = operator_min(es_matrix, src_ip, dst_ip);
#endif  // OP_MIN
#if OP_EXIST
        bool exist = operator_exist(es_matrix, src_ip, dst_ip);
#endif  // OP_EXIST
#if OP_DISTINCT
        uint32_t distinct = operator_distinct(es_matrix);
#endif  // OP_DISTINCT
#if OP_MERGE
        Matrix merged = operator_merge({es_matrix, es_matrix});
#endif  // OP_MERGE
#if OP_FILTER
        auto filter = [](uint32_t i) { return i > 1000; };
        std::unordered_map<std::pair<int, int>, uint32_t, pair_hash> filtered =
            operator_filter(es_matrix, filter);
#endif  // OP_FILTER

        // 记录结果
        auto end = std::chrono::high_resolution_clock::now();  // 记录结束时间
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            end - start);  // 计算延迟时间
        latencies.push_back(duration.count() /
                            1000.0);  // 将延迟时间转换为毫秒并存储
        total_data_size += array_len * sizeof(int) * 8;  // 累加处理的数据量
    }

    double avg_latency =
        std::accumulate(latencies.begin(), latencies.end(), 0.0) /
        latencies.size();  // 计算平均延迟
    double throughput = total_data_size / (avg_latency / 1000.0) / 1024 / 1024 /
                        1024;  // 计算吞吐量(Mb/s)

    std::cout << "Average latency: " << (avg_latency / array_len) * 1000 * 1000
              << " ns" << std::endl;
    std::cout << "Throughput: " << throughput << " Gbps" << std::endl;

    return 0;
}
