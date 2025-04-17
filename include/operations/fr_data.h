#pragma once

#include <algorithm>
#include <cstring>
#include <tuple>
#include <vector>

struct FR_Bucket {
    uint32_t FlowCount;
    uint32_t FlowXOR;
    uint32_t PacketCount;
    FR_Bucket() {
        FlowCount = 0;
        FlowXOR = 0;
        PacketCount = 0;
    }
    FR_Bucket(std::vector<uint32_t> data) {
        FlowCount = data[0];
        FlowXOR = data[1];
        PacketCount = data[2];
    }
};

typedef std::pair<std::vector<uint8_t>, std::vector<std::vector<uint32_t>>>
    FR_Data;

#define BITARRAY_LEN 40000000

FR_Data array_to_fr_data(char* data, uint32_t len);

uint32_t fr_data_to_array(const FR_Data data, char* buffer);