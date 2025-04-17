#pragma once

#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>

#define cm_json_path "../sketch_data/CountMin.json"
#define cs_json_path "../sketch_data/CountSketch.json"
#define es_json_path "../sketch_data/ElasticSketch.json"
#define hp_json_path "../sketch_data/HashPipe.json"
#define fr_json_path "../sketch_data/FlowRadar.json"
#define um_json_path "../sketch_data/UnivMon.json"
#define sl_json_path "../sketch_data/SLSketch.json"

std::vector<std::vector<int>> load_cm_from_json();
std::vector<std::vector<int>> load_cm_from_json(std::ifstream& cm_json);

std::vector<std::vector<int>> load_cs_from_json();
std::vector<std::vector<int>> load_cs_from_json(std::ifstream& cs_json);

std::vector<std::vector<int>> load_es_from_json();
std::vector<std::vector<int>> load_es_from_json(std::ifstream& es_json);

std::vector<std::vector<int>> load_hp_from_json();
std::vector<std::vector<int>> load_hp_from_json(std::ifstream& hp_json);

// std::pair<std::vector<uint8_t>, std::vector<std::vector<uint32_t>>>
// load_fr_from_json();
// std::pair<std::vector<uint8_t>, std::vector<std::vector<uint32_t>>>
// load_fr_from_json(std::ifstream& fr_json);

std::vector<std::vector<std::vector<int>>> load_um_from_json();
std::vector<std::vector<std::vector<int>>> load_um_from_json(
    std::ifstream& um_json);

std::vector<std::vector<std::vector<int>>> load_sl_from_json();
std::vector<std::vector<std::vector<int>>> load_sl_from_json(
    std::ifstream& sl_json);