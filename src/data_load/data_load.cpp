#include "data_load/data_load.h"
#include "nlohmann/json.hpp"

using std::vector;

std::vector<std::vector<int>> load_cm_from_json(std::ifstream& cm_json) {
    nlohmann::json cm_json_data;
    cm_json >> cm_json_data;
    return cm_json_data.get<std::vector<std::vector<int>>>();
}

std::vector<std::vector<int>> load_cm_from_json() {
    std::ifstream cm_json(cm_json_path);
    nlohmann::json cm_json_data;
    cm_json >> cm_json_data;
    std::vector<std::vector<int>> cm;
    cm = cm_json_data.get<vector<std::vector<int>>>();

    return cm;
};

std::vector<std::vector<int>> load_cs_from_json(std::ifstream& cs_json) {
    nlohmann::json cs_json_data;
    cs_json >> cs_json_data;
    std::vector<std::vector<int>> cs;
    cs = cs_json_data.get<vector<vector<int>>>();
    return cs;
};

std::vector<std::vector<int>> load_cs_from_json() {
    std::ifstream cs_json(cs_json_path);
    nlohmann::json cs_json_data;
    cs_json >> cs_json_data;
    std::vector<std::vector<int>> cs;
    cs = cs_json_data.get<vector<vector<int>>>();
    return cs;
};

/**
 *  第一个vector是 heavepart 的 uint32_t posvote;
    第二个vector是 heavepart 的 uint32_t negvote;
    第三个vector是 heavepart 的 bool flag;
 * @return
 */
std::vector<std::vector<int>> load_es_from_json(std::ifstream& es_json) {
    nlohmann::json es_json_data;
    es_json >> es_json_data;
    std::vector<std::vector<int>> es;
    es = es_json_data.get<vector<vector<int>>>();
    return es;
}

std::vector<std::vector<int>> load_es_from_json() {
    std::ifstream es_json(es_json_path);
    nlohmann::json es_json_data;
    es_json >> es_json_data;
    std::vector<std::vector<int>> es;
    es = es_json_data.get<vector<vector<int>>>();
    return es;
}

/**
 * 保存的是 hashpipe 的 val
 * @return
 */
std::vector<std::vector<int>> load_hp_from_json(std::ifstream& hp_json) {
    nlohmann::json hp_json_data;
    hp_json >> hp_json_data;
    std::vector<std::vector<int>> hp;
    hp = hp_json_data.get<vector<vector<int>>>();
    return hp;
}

std::vector<std::vector<int>> load_hp_from_json() {
    std::ifstream hp_json(hp_json_path);
    nlohmann::json hp_json_data;
    hp_json >> hp_json_data;
    std::vector<std::vector<int>> hp;
    hp = hp_json_data.get<vector<vector<int>>>();
    return hp;
}

/**
 * 返回一个 pair
 * first : fr.BloomFilter.bitarray 长度：40000000
 * second : countingtable {    u_int64_t FlowXOR;
                               u_int32_t FlowCount;
                               u_int32_t PacketCount;} 长度：315200
 * @return
 */
std::pair<std::vector<uint8_t>, std::vector<std::vector<uint32_t>>>
load_fr_from_json(std::ifstream& fr_json) {
    nlohmann::json fr_json_data;
    fr_json >> fr_json_data;
    std::vector<uint8_t> bit_array;
    std::vector<std::vector<uint32_t>> countingtable_data;

    bit_array = fr_json_data["bitArray"].get<std::vector<uint8_t>>();
    countingtable_data =
        fr_json_data["countingtable"].get<std::vector<std::vector<uint32_t>>>();

    return std::make_pair(bit_array, countingtable_data);
}

std::pair<std::vector<uint8_t>, std::vector<std::vector<uint32_t>>>
load_fr_from_json() {
    std::ifstream fr_json(fr_json_path);
    nlohmann::json fr_json_data;
    fr_json >> fr_json_data;
    std::vector<uint8_t> bit_array;
    std::vector<std::vector<uint32_t>> countingtable_data;

    bit_array = fr_json_data["bitArray"].get<std::vector<uint8_t>>();
    countingtable_data =
        fr_json_data["countingtable"].get<std::vector<std::vector<uint32_t>>>();

    return std::make_pair(bit_array, countingtable_data);
}

/**
 * UnivMon<8, TOTAL_MEM, 12> um;
 * 12 个 L2HitterDetector
 * 每个 L2HitterDetector 有2个 cm_sketch 其中每个 cm_sketch 的长度是12
 * @return
 */
std::vector<std::vector<std::vector<int>>> load_um_from_json(
    std::ifstream& um_json) {
    nlohmann::json um_json_data;
    um_json >> um_json_data;
    std::vector<std::vector<std::vector<int>>> um;
    um = um_json_data.get<std::vector<std::vector<std::vector<int>>>>();
    return um;
}

std::vector<std::vector<std::vector<int>>> load_um_from_json() {
    std::ifstream um_json(um_json_path);
    nlohmann::json um_json_data;
    um_json >> um_json_data;
    std::vector<std::vector<std::vector<int>>> um;
    um = um_json_data.get<std::vector<std::vector<std::vector<int>>>>();
    return um;
}

/**
 * UnivMon<8, TOTAL_MEM, 12> um;
 * 12 个 L2HitterDetector
 * 每个 L2HitterDetector 有2个 cm_sketch 其中每个 cm_sketch 的长度是12
 * @return
 */
std::vector<std::vector<std::vector<int>>> load_sl_from_json(
    std::ifstream& sl_json) {
    nlohmann::json sl_json_data;
    sl_json >> sl_json_data;
    std::vector<std::vector<std::vector<int>>> sl;
    sl = sl_json_data.get<std::vector<std::vector<std::vector<int>>>>();
    return sl;
}

std::vector<std::vector<std::vector<int>>> load_sl_from_json() {
    std::ifstream sl_json(sl_json_path);
    nlohmann::json sl_json_data;
    sl_json >> sl_json_data;
    std::vector<std::vector<std::vector<int>>> sl;
    sl = sl_json_data.get<std::vector<std::vector<std::vector<int>>>>();
    return sl;
}