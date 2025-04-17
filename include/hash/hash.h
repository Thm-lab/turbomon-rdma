#pragma once

#include <cstdint>
#include "hash/MurmurHash3.h"
#include "hash/seed_list.h"

/*
    content: |<-- srcIP -->| uint32_t
    index :  [0] [1] [2] [3]
    content: |<-- dstIP -->| uint32_t
    index :  [0] [1] [2] [3]
*/
typedef struct {
    uint32_t src_ip;
    uint32_t dst_ip;
} two_tuple;

// key是cm不同行的索引（从0开始），从而实现8行hash函数结果不同
// len是哈希数组的长度
uint64_t two_tuple_hash(uint32_t src_ip,
                        uint32_t dst_ip,
                        uint64_t key,
                        int64_t len);

uint64_t two_tuple_hash(two_tuple tuple, uint64_t key, int64_t len);
