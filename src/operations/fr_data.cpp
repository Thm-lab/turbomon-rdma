#include "operations/fr_data.h"

FR_Data array_to_fr_data(char* data, uint32_t len) {
    std::vector<uint8_t> bitarray(BITARRAY_LEN);
    std::transform(data, data + BITARRAY_LEN, bitarray.begin(),
                   [](char x) { return static_cast<uint8_t>(x); });

    std::vector<std::vector<uint32_t>> countingtable_data;
    struct FR_Bucket* fr_bucket = (struct FR_Bucket*)(data + bitarray.size());

    for (int i = 0; i < (len - BITARRAY_LEN) / sizeof(struct FR_Bucket); ++i) {
        countingtable_data.push_back({fr_bucket[i].FlowCount,
                                      fr_bucket[i].FlowXOR,
                                      fr_bucket[i].PacketCount});
    }

    return std::make_pair(bitarray, countingtable_data);
}

uint32_t fr_data_to_array(const FR_Data data, char* buffer) {
    const auto& bitarray = data.first;
    const auto& countingtable = data.second;

    // 计算总长度
    uint32_t offset =
        bitarray.size() + countingtable.size() * sizeof(FR_Bucket);

    // bitarray
    std::memcpy(buffer, bitarray.data(), bitarray.size());

    // countingtable
    char* current_pos = buffer + bitarray.size();
    for (const auto& vec : countingtable) {
        std::memcpy(current_pos, vec.data(), sizeof(FR_Bucket));
        current_pos += sizeof(FR_Bucket);
    }

    return offset;
}