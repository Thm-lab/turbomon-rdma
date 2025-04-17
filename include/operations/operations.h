#pragma once

#include <algorithm>
#include <unordered_map>

#include "hash/hash.h"
#include "operations/fr_data.h"
#include "operations/matrix.h"

uint32_t operator_max(const Matrix& data, two_tuple tuple);
uint32_t operator_max(const Matrixs& data, two_tuple tuple);

uint32_t operator_min(const Matrix& data, two_tuple tuple);
uint32_t operator_min(const Matrixs& data, two_tuple tuple);

bool operator_exist(const Matrix& data, two_tuple tuple);
bool operator_exist(const Matrixs& data, two_tuple tuple);

uint32_t operator_distinct(const Matrix& data);
uint32_t operator_distinct(const Matrixs& data);

Matrix operator_merge(const std::vector<Matrix>& matrixs);
Matrixs operator_merge(const std::vector<Matrixs>& matrixs);

// 用pair作为key的哈希函数
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ hash2;
    }
};

// 返回符合条件的行、列的索引(pair<row,column>) 和 值
std::unordered_map<std::pair<int, int>, uint32_t, pair_hash> operator_filter(
    const Matrix& data,
    bool (*condition)(uint32_t));

// 返回不同sketch 符合条件的行、列的索引(pair<row,column>) 和 值 的数组
std::vector<std::unordered_map<std::pair<int, int>, uint32_t, pair_hash>>
operator_filter(const Matrixs& data, bool (*condition)(uint32_t));

/*
模板函数：提供直接传两元组结构和分别传ip的算子API
*/
template <typename T>
uint32_t operator_max(const T& data, uint32_t src_ip, uint32_t dst_ip) {
    two_tuple tuple = {src_ip, dst_ip};
    return operator_max(data, tuple);
}

template <typename T>
uint32_t operator_min(const T& data, uint32_t src_ip, uint32_t dst_ip) {
    two_tuple tuple = {src_ip, dst_ip};
    return operator_min(data, tuple);
}

template <typename T>
bool operator_exist(const T& data, uint32_t src_ip, uint32_t dst_ip) {
    two_tuple tuple = {src_ip, dst_ip};
    return operator_exist(data, tuple);
}