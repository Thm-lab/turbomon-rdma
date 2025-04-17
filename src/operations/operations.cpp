#include "operations/operations.h"

uint32_t operator_max(const Matrix& data, two_tuple tuple) {
    // 逐行寻找最大值
    uint32_t result = 0;
    for (int i = 0; i < data.size(); i++) {
        uint64_t j = two_tuple_hash(tuple, (uint64_t)i, (int64_t)data.size());
        result = std::max(result, (uint32_t)data[i][j]);
    }
    return result;
}

uint32_t operator_max(const Matrixs& data, two_tuple tuple) {
    uint32_t result = 0;
    for (Matrix m : data) {
        result = std::max(operator_max(m, tuple), result);
    }
    return result;
}

uint32_t operator_min(const Matrix& data, two_tuple tuple) {
    // 逐行寻找最小值
    uint32_t result = 0xffffffff;
    for (int i = 0; i < data.size(); i++) {
        uint64_t j = two_tuple_hash(tuple, (uint64_t)i, (int64_t)data.size());
        result = std::min(result, (uint32_t)data[i][j]);
    }
    return result;
}

uint32_t operator_min(const Matrixs& data, two_tuple tuple) {
    uint32_t result = 0xffffffff;
    for (Matrix m : data) {
        result = std::min(operator_max(m, tuple), result);
    }
    return result;
}

bool operator_exist(const Matrix& data, two_tuple tuple) {
    for (int i = 0; i < data.size(); i++) {
        uint64_t j = two_tuple_hash(tuple, (uint64_t)i, (int64_t)data.size());
        if (data[i][j] != 0) {
            return true;
        }
    }
    return false;
}

bool operator_exist(const Matrixs& data, two_tuple tuple) {
    bool result = false;
    for (Matrix m : data) {
        result = result || operator_exist(m, tuple);
    }
    return result;
}

uint32_t operator_distinct(const Matrix& data) {
    uint32_t result = 0;
    for (int i = 0; i < data.size(); i++) {
        uint32_t row_sum = 0;
        for (int j = 0; j < data[i].size(); j++) {
            if (data[i][j] != 0) {
                row_sum++;
            }
        }
        std::max(result, row_sum);
    }
    return result;
}

uint32_t operator_distinct(const Matrixs& data) {
    uint32_t result = 0;
    for (Matrix m : data) {
        result += operator_distinct(m);
    }
    return result;
}

Matrix operator_merge(const std::vector<Matrix>& matrixs) {
    if (matrixs.size() == 0) {
        return Matrix();
    } else if (matrixs.size() == 1) {
        return matrixs[0];
    }
    uint32_t row = matrixs[0].size(), columns = matrixs[0][0].size();
    Matrix result(row, std::vector<int>(columns, 0));
    for (auto& source : matrixs) {
        for (int i = 0; i < source.size(); i++) {
            for (int j = 0; j < source[i].size(); j++) {
                result[i][j] += source[i][j];
            }
        }
    }
    return result;
}

Matrixs operator_merge(const std::vector<Matrixs>& matrixs) {
    if (matrixs.size() == 0) {
        return Matrixs();
    } else if (matrixs.size() == 1) {
        return matrixs[0];
    }
    Matrixs result;
    std::vector<Matrix> need_merge;
    for (int i = 0; i < matrixs[0].size(); i++) {
        for (Matrixs ms : matrixs) {
            need_merge.emplace_back(ms[i]);
        }
        result.emplace_back(operator_merge(need_merge));
    }
    return result;
}

std::unordered_map<std::pair<int, int>, uint32_t, pair_hash> operator_filter(
    const Matrix& data,
    bool (*condition)(uint32_t)) {
    std::unordered_map<std::pair<int, int>, uint32_t, pair_hash> result;
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            if (condition(data[i][j])) {
                result[{i, j}] = data[i][j];
            }
        }
    }
    return result;
}

std::vector<std::unordered_map<std::pair<int, int>, uint32_t, pair_hash>>
operator_filter(const Matrixs& data, bool (*condition)(uint32_t)) {
    std::vector<std::unordered_map<std::pair<int, int>, uint32_t, pair_hash>>
        result;
    for (Matrix m : data) {
        result.emplace_back(operator_filter(m, condition));
    }
    return result;
}