#include "hash/hash.h"

uint64_t two_tuple_hash(uint32_t src_ip,
                        uint32_t dst_ip,
                        uint64_t key,
                        int64_t len) {
    uint64_t k1, k2, result;
    k1 = (uint64_t)src_ip;
    k2 = (uint64_t)dst_ip;

    uint64_t combined_k;
    combined_k = (k1 << 32) + k2;

    // convert uint64 to an array of uint8 variables
    uint8_t* p = (uint8_t*)&combined_k;
    uint8_t key_bytes[8];
    for (int i = 0; i < 8; i++) {
        key_bytes[i] = p[i];
    }
    // hash
    uint64_t key_len = 8;
    uint64_t seed = seed_list[(key) % SEED_LIST_SIZE];
    uint64_t mmh3_result[2];
    MurmurHash3_x64_128((const char*)key_bytes, key_len, seed, mmh3_result);

    result = mmh3_result[0];
    int64_t tmp = (int64_t)result % len;
    if (tmp < 0) {
        tmp += len;
    }
    return uint64_t(tmp);
}

uint64_t two_tuple_hash(two_tuple tuple, uint64_t key, int64_t len) {
    return two_tuple_hash(tuple.src_ip, tuple.dst_ip, key, len);
}